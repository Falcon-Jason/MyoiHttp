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
include Socket/CMakeFiles/Socket.dir/depend.make

# Include the progress variables for this target.
include Socket/CMakeFiles/Socket.dir/progress.make

# Include the compile flags for this target's objects.
include Socket/CMakeFiles/Socket.dir/flags.make

Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o: Socket/CMakeFiles/Socket.dir/flags.make
Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o: ../src/Ipv4Addr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o -c /home/jason/Documents/repos/JBProjects/Network/src/Ipv4Addr.cpp

Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/Network/src/Ipv4Addr.cpp > CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.i

Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/Network/src/Ipv4Addr.cpp -o CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.s

Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o: Socket/CMakeFiles/Socket.dir/flags.make
Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o: ../src/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o -c /home/jason/Documents/repos/JBProjects/Network/src/TcpServer.cpp

Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Socket.dir/__/src/TcpServer.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/Network/src/TcpServer.cpp > CMakeFiles/Socket.dir/__/src/TcpServer.cpp.i

Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Socket.dir/__/src/TcpServer.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/Network/src/TcpServer.cpp -o CMakeFiles/Socket.dir/__/src/TcpServer.cpp.s

Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o: Socket/CMakeFiles/Socket.dir/flags.make
Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o: ../src/TcpConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o -c /home/jason/Documents/repos/JBProjects/Network/src/TcpConnection.cpp

Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.i"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jason/Documents/repos/JBProjects/Network/src/TcpConnection.cpp > CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.i

Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.s"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jason/Documents/repos/JBProjects/Network/src/TcpConnection.cpp -o CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.s

# Object files for target Socket
Socket_OBJECTS = \
"CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o" \
"CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o" \
"CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o"

# External object files for target Socket
Socket_EXTERNAL_OBJECTS =

Socket/libSocket.a: Socket/CMakeFiles/Socket.dir/__/src/Ipv4Addr.cpp.o
Socket/libSocket.a: Socket/CMakeFiles/Socket.dir/__/src/TcpServer.cpp.o
Socket/libSocket.a: Socket/CMakeFiles/Socket.dir/__/src/TcpConnection.cpp.o
Socket/libSocket.a: Socket/CMakeFiles/Socket.dir/build.make
Socket/libSocket.a: Socket/CMakeFiles/Socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libSocket.a"
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && $(CMAKE_COMMAND) -P CMakeFiles/Socket.dir/cmake_clean_target.cmake
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Socket/CMakeFiles/Socket.dir/build: Socket/libSocket.a

.PHONY : Socket/CMakeFiles/Socket.dir/build

Socket/CMakeFiles/Socket.dir/clean:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket && $(CMAKE_COMMAND) -P CMakeFiles/Socket.dir/cmake_clean.cmake
.PHONY : Socket/CMakeFiles/Socket.dir/clean

Socket/CMakeFiles/Socket.dir/depend:
	cd /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jason/Documents/repos/JBProjects/Network /home/jason/Documents/repos/JBProjects/Network/Socket /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket /home/jason/Documents/repos/JBProjects/Network/cmake-build-debug/Socket/CMakeFiles/Socket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Socket/CMakeFiles/Socket.dir/depend

