cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# specify name of the project and specify which language to compile for
project(point-visualizer LANGUAGES CXX)

#-----------------------------------------------------------------------------#
# define the asset path in c++
set(ASSETS_DIR ${PROJECT_SOURCE_DIR}/assets)
add_compile_definitions(ASSETS_PATH="${ASSETS_DIR}")

#-----------------------------------------------------------------------------#
# list of all source files
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.h")
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${ASSETS_DIR}/shaders/*.glsl")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add dependencies
include(cmake/CPM.cmake)

# GLAD
CPMAddPackage(
  NAME glad
  GITHUB_REPOSITORY Dav1dde/glad
  VERSION 0.1.33
)

# GLM
CPMAddPackage(
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 0.9.9.7
)

# GLFW
CPMAddPackage(
  NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
	"GLFW_BUILD_TESTS Off"
	"GLFW_BUILD_EXAMPLES Off"
	"GLFW_BUILD_DOCS Off"
    "GLFW_INSTALL Off"
    "GLFW_USE_HYBRID_HPG On"
)

CPMAddPackage(
    NAME LAStools 
    GITHUB_REPOSITORY LAStools/LAStools
    VERSION 2.0.2
)
# Fix a bug in LASlib wherein these directories can't be found if not being built directly by CMake
target_include_directories(LASlib PRIVATE ${LAStools_SOURCE_DIR}/LASzip/src ${LAStools_SOURCE_DIR}/LASlib/inc)

# Exclude all the targets from the main CMakeLists.txt that is within LAStools, leaving only LASlib
set(GEOPROJECTION_TARGETS
	laszip
	lasinfo
	lasprecision
	txt2las
	las2las
	lasmerge
)
set(STANDALONE_TARGETS
	las2txt
	lasdiff
	lasindex
)
set_target_properties(${GEOPROJECTION_TARGETS} ${STANDALONE_TARGETS} PROPERTIES EXCLUDE_FROM_ALL true)

# put all external targets into a seperate folder to not pollute the project folder
set_target_properties(glad glad-generate-files glfw LASlib PROPERTIES FOLDER ExternalTargets)

# Source file grouping of visual studio and xcode
CPMAddPackage(
  NAME GroupSourcesByFolder.cmake
  GITHUB_REPOSITORY TheLartians/GroupSourcesByFolder.cmake
  VERSION 1.0
)

#-----------------------------------------------------------------------------#
# list all files that will either be used for compilation or that should show 
# up in the ide of your choice
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} ${SHADER_FILES})
GroupSourcesByFolder(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC src)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11) # use c++11

# specify libraries to link with after compilation
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm LASlib)