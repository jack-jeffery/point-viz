CPMAddPackage(NAME LAStools 
              GITHUB_REPOSITORY LAStools/LAStools
              VERSION 2.0.2)

message(PROJECT_SOURCE_DIR="${LAStools_SOURCE_DIR}/LASlib/inc")
# FILE(GLOB LASlib_sources ${LAStools_SOURCE_DIR}/LASlib/*.cpp)
# add_library(LASlib STATIC ${LASlib_sources})
include_directories(${LAStools_SOURCE_DIR}/LASzip/src ${LAStools_SOURCE_DIR}/LASlib/inc)
target_include_directories(LASlib PRIVATE ${LAStools_SOURCE_DIR}/LASzip/src ${LAStools_SOURCE_DIR}/LASlib/inc)
add_executable(PointVisualizer point_visualizer.cxx)
add_dependencies(PointVisualizer LASlib)
target_link_libraries(PointVisualizer PRIVATE LASlib)

