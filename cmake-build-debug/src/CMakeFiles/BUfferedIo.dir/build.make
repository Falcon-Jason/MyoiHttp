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
include src/CMakeFiles/BUfferedIo.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/BUfferedIo.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/BUfferedIo.dir/flags.make

src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o: src/CMakeFiles/BUfferedIo.dir/flags.make
src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o: ../src/BufferedIo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o -c /home/jason/Documents/repos/JBProjects/Network/src/BufferedIo.cpp

src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/Network/src/BufferedIo.cpp > CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.i

src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/Network/src/BufferedIo.cpp -o CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.s

# Object files for target BUfferedIo
BUfferedIo_OBJECTS = \
"CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o"

# External object files for target BUfferedIo
BUfferedIo_EXTERNAL_OBJECTS =

src/libBUfferedIo.a: src/CMakeFiles/BUfferedIo.dir/BufferedIo.cpp.o
src/libBUfferedIo.a: src/CMakeFiles/BUfferedIo.dir/build.make
src/libBUfferedIo.a: src/CMakeFiles/BUfferedIo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libBUfferedIo.a"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/BUfferedIo.dir/cmake_clean_target.cmake
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BUfferedIo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/BUfferedIo.dir/build: src/libBUfferedIo.a

.PHONY : src/CMakeFiles/BUfferedIo.dir/build

src/CMakeFiles/BUfferedIo.dir/clean:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/BUfferedIo.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/BUfferedIo.dir/clean

src/CMakeFiles/BUfferedIo.dir/depend:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jason/Documents/repos/JBProjects/Network /home/jason/Documents/repos/JBProjects/Network/src /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/src/CMakeFiles/BUfferedIo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/BUfferedIo.dir/depend

