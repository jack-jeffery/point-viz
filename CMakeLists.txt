cmake_minimum_required(VERSION 3.15)

project(PointVisualizer)
project(PointVisualizer VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add dependencies
include(cmake/CPM.cmake)

add_subdirectory(point_visualizer)