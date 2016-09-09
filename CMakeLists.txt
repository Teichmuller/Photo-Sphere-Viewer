cmake_minimum_required(VERSION 3.4)
project(PhotoSphereViewer)

message(AUTHOR_WARNING "This project are not well supported on vast of platforms. \
Configurations are intended for g++ series toolchain and \
may not work properly with other toolchains.")

# not applicable at present
# option(CMAKE_BUILD_TYPE "Choose build type" Debug)
set(CMAKE_BUILD_TYPE Debug)

#add_compile_options(-std=c++11 -Wall)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

# Configure CXPL
add_subdirectory(CXPL)
set(CXPL_INCLUDE_COPY_TO_PATH "${CMAKE_SOURCE_DIR}/include")
set(CXPL_INCLUDE_COPY_FROM_PATH "${CMAKE_SOURCE_DIR}/CXPL/include/CXPL")
message("CXPL_INCLUDE_COPY_TO_PATH: ${CXPL_INCLUDE_COPY_TO_PATH}")
if(EXISTS "${CXPL_INCLUDE_COPY_TO_PATH}/CXPL")
	message("Remove previous CXPL include directory...")
	file(REMOVE_RECURSE "${CXPL_INCLUDE_COPY_TO_PATH}/CXPL")
else()
	message("CXPL doesn't exist...")
endif()
message("Copy CXPL...")
file(COPY ${CXPL_INCLUDE_COPY_FROM_PATH} DESTINATION ${CXPL_INCLUDE_COPY_TO_PATH})

# Compile
set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/include")
include_directories(${CMAKE_INCLUDE_PATH})
add_subdirectory(src)

add_executable(PhotoSphereViewer $<TARGET_OBJECTS:PhotoSphere> main.cpp)
target_link_libraries(PhotoSphereViewer CXPL exiv2 opengl32 freeglut glew32 freeimage)

# add_custom_command(TARGET PhotoSphereViewer PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
	# ${CMAKE_SOURCE_DIR}/CXPL/include
	# ${CMAKE_SOURCE_DIR}/include/CXPL)

# Copy neccessary files
add_custom_command(TARGET PhotoSphereViewer POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/shader.vert
	${CMAKE_SOURCE_DIR}/shader.frag
	${CMAKE_SOURCE_DIR}/TestImage.jpg
	${CMAKE_CURRENT_BINARY_DIR})