include(FetchContent)

# FetchContent_Declare(LASlib_download
#     GIT_REPOSITORY https://github.com/LAStools/LAStools.git
#     GIT_TAG v2.0.2
# )
# FetchContent_MakeAvailable(LASlib_download)

include(ExternalProject)
ExternalProject_Add(LASlibDownload
    PREFIX 3rd_party
    GIT_REPOSITORY https://github.com/LAStools/LAStools.git
    GIT_TAG v2.0.2
    INSTALL_COMMAND ""
    LOG_BUILD ON
    LOG_CONFIGURE ON
)

set(LASLIB_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/src/LASlibDownload/LASlib/inc)
set(LASZIP_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/src/LASlibDownload/LASzip/src)
set(LASLIB_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rd_party/src/LASlibDownload/LASlib/lib)

add_library(LASlib SHARED IMPORTED)
set_target_properties(LASlib PROPERTIES IMPORTED_LOCATION ${LASLIB_LIB_DIR}/libLASlib.a)

include_directories(${LASLIB_INCLUDE_DIR} ${LASZIP_INCLUDE_DIR})
add_executable(PointVisualizer point_visualizer.cxx)
target_link_libraries(PointVisualizer PRIVATE LASlib)
add_dependencies(PointVisualizer LASlibDownload)