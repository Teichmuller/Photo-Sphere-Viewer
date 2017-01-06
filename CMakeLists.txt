cmake_minimum_required(VERSION 3.4)
project(PhotoSphereViewer)

message(AUTHOR_WARNING "This project are not well supported on vast of platforms. \
Configurations are intended for g++ series toolchain and \
may not work properly with other toolchains.")

# not applicable at present
# option(CMAKE_BUILD_TYPE "Choose build type" Debug)
set(CMAKE_BUILD_TYPE Debug)

#add_compile_options(-std=c++11 -Wall)
if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
endif()

# Check Dependencies
include(cmake/dependencies.cmake)
include_directories(${Dependencies_INCLUDE_DIRS})

# Configure CXPL
set(cxpl_BUILD_TESTS OFF)
set(cxpl_BUILD_TOOLS OFF)
add_subdirectory(packages/cxpl)
include_directories(${CMAKE_SOURCE_DIR}/packages/cxpl/include)

# Compile
include_directories(${CMAKE_SOURCE_DIR}/include)
message("Include paths: ${CMAKE_INCLUDE_PATH}")
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
# configure NuGet
if (MSVC)
	execute_process(COMMAND nuget restore ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.sln)
endif()
