# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jason/Documents/repos/JBProjects/MyoiHttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/MyoiHttp_EchoClient.dir/depend.make
# Include the progress variables for this target.
include src/CMakeFiles/MyoiHttp_EchoClient.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MyoiHttp_EchoClient.dir/flags.make

src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o: src/CMakeFiles/MyoiHttp_EchoClient.dir/flags.make
src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o: ../src/echo/EchoClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o -c /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/EchoClient.cpp

src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/EchoClient.cpp > CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.i

src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/EchoClient.cpp -o CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.s

# Object files for target MyoiHttp_EchoClient
MyoiHttp_EchoClient_OBJECTS = \
"CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o"

# External object files for target MyoiHttp_EchoClient
MyoiHttp_EchoClient_EXTERNAL_OBJECTS =

src/MyoiHttp_EchoClient: src/CMakeFiles/MyoiHttp_EchoClient.dir/echo/EchoClient.cpp.o
src/MyoiHttp_EchoClient: src/CMakeFiles/MyoiHttp_EchoClient.dir/build.make
src/MyoiHttp_EchoClient: src/libMyoiHttp_Core.a
src/MyoiHttp_EchoClient: src/CMakeFiles/MyoiHttp_EchoClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyoiHttp_EchoClient"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyoiHttp_EchoClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MyoiHttp_EchoClient.dir/build: src/MyoiHttp_EchoClient
.PHONY : src/CMakeFiles/MyoiHttp_EchoClient.dir/build

src/CMakeFiles/MyoiHttp_EchoClient.dir/clean:
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/MyoiHttp_EchoClient.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MyoiHttp_EchoClient.dir/clean

src/CMakeFiles/MyoiHttp_EchoClient.dir/depend:
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jason/Documents/repos/JBProjects/MyoiHttp /home/jason/Documents/repos/JBProjects/MyoiHttp/src /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/src/CMakeFiles/MyoiHttp_EchoClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MyoiHttp_EchoClient.dir/depend

