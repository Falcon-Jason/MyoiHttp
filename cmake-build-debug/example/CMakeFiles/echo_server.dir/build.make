# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
include example/CMakeFiles/echo_server.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/echo_server.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/echo_server.dir/flags.make

example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o: example/CMakeFiles/echo_server.dir/flags.make
example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o: ../src/echo/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o -c /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/server.cpp

example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/__/src/echo/server.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/server.cpp > CMakeFiles/echo_server.dir/__/src/echo/server.cpp.i

example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/__/src/echo/server.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/MyoiHttp/src/echo/server.cpp -o CMakeFiles/echo_server.dir/__/src/echo/server.cpp.s

# Object files for target echo_server
echo_server_OBJECTS = \
"CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o"

# External object files for target echo_server
echo_server_EXTERNAL_OBJECTS =

example/echo_server: example/CMakeFiles/echo_server.dir/__/src/echo/server.cpp.o
example/echo_server: example/CMakeFiles/echo_server.dir/build.make
example/echo_server: src/libnetwork_core.a
example/echo_server: example/CMakeFiles/echo_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable echo_server"
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/echo_server.dir/build: example/echo_server

.PHONY : example/CMakeFiles/echo_server.dir/build

example/CMakeFiles/echo_server.dir/clean:
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example && $(CMAKE_COMMAND) -P CMakeFiles/echo_server.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/echo_server.dir/clean

example/CMakeFiles/echo_server.dir/depend:
	cd /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jason/Documents/repos/JBProjects/MyoiHttp /home/jason/Documents/repos/JBProjects/MyoiHttp/example /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example /home/jason/Documents/repos/JBProjects/MyoiHttp/cmake-build-debug/example/CMakeFiles/echo_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/echo_server.dir/depend

