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
CMAKE_SOURCE_DIR = /home/jason/Documents/repos/JBProjects/Network

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug

# Include any dependencies generated for this target.
include test/CMakeFiles/Test_Core.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/Test_Core.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/Test_Core.dir/flags.make

test/CMakeFiles/Test_Core.dir/Test_Core.cpp.o: test/CMakeFiles/Test_Core.dir/flags.make
test/CMakeFiles/Test_Core.dir/Test_Core.cpp.o: ../test/Test_Core.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/Test_Core.dir/Test_Core.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Test_Core.dir/Test_Core.cpp.o -c /home/jason/Documents/repos/JBProjects/Network/test/Test_Core.cpp

test/CMakeFiles/Test_Core.dir/Test_Core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Test_Core.dir/Test_Core.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/Network/test/Test_Core.cpp > CMakeFiles/Test_Core.dir/Test_Core.cpp.i

test/CMakeFiles/Test_Core.dir/Test_Core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Test_Core.dir/Test_Core.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/Network/test/Test_Core.cpp -o CMakeFiles/Test_Core.dir/Test_Core.cpp.s

# Object files for target Test_Core
Test_Core_OBJECTS = \
"CMakeFiles/Test_Core.dir/Test_Core.cpp.o"

# External object files for target Test_Core
Test_Core_EXTERNAL_OBJECTS =

test/Test_Core: test/CMakeFiles/Test_Core.dir/Test_Core.cpp.o
test/Test_Core: test/CMakeFiles/Test_Core.dir/build.make
test/Test_Core: src/libnetwork_core.a
test/Test_Core: test/CMakeFiles/Test_Core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Test_Core"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Test_Core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/Test_Core.dir/build: test/Test_Core

.PHONY : test/CMakeFiles/Test_Core.dir/build

test/CMakeFiles/Test_Core.dir/clean:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/Test_Core.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/Test_Core.dir/clean

test/CMakeFiles/Test_Core.dir/depend:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jason/Documents/repos/JBProjects/Network /home/jason/Documents/repos/JBProjects/Network/test /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/test/CMakeFiles/Test_Core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/Test_Core.dir/depend

