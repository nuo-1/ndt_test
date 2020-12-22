cmake_minimum_required(VERSION 3.17)
project(ndt_test)

set(CMAKE_CXX_STANDARD 14)

find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(ndt_test main.cpp)
target_link_libraries(ndt_test ${PCL_LIBRARIES})

