# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = C:/msys64/mingw64/bin/cmake.exe

# The command to remove a file.
RM = C:/msys64/mingw64/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/msys64/home/eecur/PhotoSphereViewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug

# Include any dependencies generated for this target.
include packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/depend.make

# Include the progress variables for this target.
include packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/progress.make

# Include the compile flags for this target's objects.
include packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/flags.make

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/flags.make
packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/includes_CXX.rsp
packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj: ../packages/cxpl/src/tests/Core/ErrorHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj"
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj -c C:/msys64/home/eecur/PhotoSphereViewer/packages/cxpl/src/tests/Core/ErrorHandler.cpp

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.i"
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/msys64/home/eecur/PhotoSphereViewer/packages/cxpl/src/tests/Core/ErrorHandler.cpp > CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.i

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.s"
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/msys64/home/eecur/PhotoSphereViewer/packages/cxpl/src/tests/Core/ErrorHandler.cpp -o CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.s

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.requires:

.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.requires

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.provides: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.requires
	$(MAKE) -f packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/build.make packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.provides.build
.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.provides

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.provides.build: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj


# Object files for target ErrorHandler
ErrorHandler_OBJECTS = \
"CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj"

# External object files for target ErrorHandler
ErrorHandler_EXTERNAL_OBJECTS =

packages/cxpl/src/tests/Core/ErrorHandler.exe: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj
packages/cxpl/src/tests/Core/ErrorHandler.exe: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/build.make
packages/cxpl/src/tests/Core/ErrorHandler.exe: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/linklibs.rsp
packages/cxpl/src/tests/Core/ErrorHandler.exe: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ErrorHandler.exe"
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/cmake.exe -E remove -f CMakeFiles/ErrorHandler.dir/objects.a
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/ar.exe cr CMakeFiles/ErrorHandler.dir/objects.a @CMakeFiles/ErrorHandler.dir/objects1.rsp
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && C:/msys64/mingw64/bin/g++.exe   -std=c++11 -Wall -std=c++11  -std=c++11 -Wall -g   -Wl,--whole-archive CMakeFiles/ErrorHandler.dir/objects.a -Wl,--no-whole-archive  -o ErrorHandler.exe -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/ErrorHandler.dir/linklibs.rsp

# Rule to build all files generated by this target.
packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/build: packages/cxpl/src/tests/Core/ErrorHandler.exe

.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/build

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/requires: packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/ErrorHandler.cpp.obj.requires

.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/requires

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/clean:
	cd C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core && $(CMAKE_COMMAND) -P CMakeFiles/ErrorHandler.dir/cmake_clean.cmake
.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/clean

packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/msys64/home/eecur/PhotoSphereViewer C:/msys64/home/eecur/PhotoSphereViewer/packages/cxpl/src/tests/Core C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core C:/msys64/home/eecur/PhotoSphereViewer/Build-Debug/packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : packages/cxpl/src/tests/Core/CMakeFiles/ErrorHandler.dir/depend

