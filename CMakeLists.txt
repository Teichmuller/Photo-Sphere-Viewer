cmake_minimum_required(VERSION 3.4)
project(PhotoSphereViewer)

# not applicable at present
# option(CMAKE_BUILD_TYPE "Choose build type" Debug)
set(CMAKE_BUILD_TYPE Debug)

# Check Dependencies
include(cmake/dependencies.cmake)
include_directories(${Dependencies_INCLUDE_DIRS})

# Configure CXPL
include_directories(${CMAKE_SOURCE_DIR}/packages/cxpl/include)

# Compile
include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)

add_executable(PhotoSphereViewer $<TARGET_OBJECTS:PhotoSphere> main.cpp)
target_link_libraries(PhotoSphereViewer PUBLIC ${Dependencies_LIBRARIES})

# Copy neccessary files
add_custom_command(TARGET PhotoSphereViewer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/data/shader.vert
    ${CMAKE_SOURCE_DIR}/data/shader.frag
    ${CMAKE_SOURCE_DIR}/data/TestImage.jpg
    ${CMAKE_SOURCE_DIR}/data/Test1.jpg
	${CMAKE_CURRENT_BINARY_DIR})
