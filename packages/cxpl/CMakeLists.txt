cmake_minimum_required(VERSION 3.4)

project(cxpl)

option(cxpl_BUILD_TESTS "" ON)
option(cxpl_BUILD_TOOLS "" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("include")
add_subdirectory(src)
