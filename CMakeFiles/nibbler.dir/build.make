# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sassyrog/Desktop/Nibbler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sassyrog/Desktop/Nibbler

# Include any dependencies generated for this target.
include CMakeFiles/nibbler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/nibbler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/nibbler.dir/flags.make

CMakeFiles/nibbler.dir/main.cpp.o: CMakeFiles/nibbler.dir/flags.make
CMakeFiles/nibbler.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sassyrog/Desktop/Nibbler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/nibbler.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nibbler.dir/main.cpp.o -c /home/sassyrog/Desktop/Nibbler/main.cpp

CMakeFiles/nibbler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nibbler.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sassyrog/Desktop/Nibbler/main.cpp > CMakeFiles/nibbler.dir/main.cpp.i

CMakeFiles/nibbler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nibbler.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sassyrog/Desktop/Nibbler/main.cpp -o CMakeFiles/nibbler.dir/main.cpp.s

CMakeFiles/nibbler.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/nibbler.dir/main.cpp.o.requires

CMakeFiles/nibbler.dir/main.cpp.o.provides: CMakeFiles/nibbler.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/nibbler.dir/build.make CMakeFiles/nibbler.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/nibbler.dir/main.cpp.o.provides

CMakeFiles/nibbler.dir/main.cpp.o.provides.build: CMakeFiles/nibbler.dir/main.cpp.o


# Object files for target nibbler
nibbler_OBJECTS = \
"CMakeFiles/nibbler.dir/main.cpp.o"

# External object files for target nibbler
nibbler_EXTERNAL_OBJECTS =

nibbler: CMakeFiles/nibbler.dir/main.cpp.o
nibbler: CMakeFiles/nibbler.dir/build.make
nibbler: CMakeFiles/nibbler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sassyrog/Desktop/Nibbler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nibbler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nibbler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/nibbler.dir/build: nibbler

.PHONY : CMakeFiles/nibbler.dir/build

CMakeFiles/nibbler.dir/requires: CMakeFiles/nibbler.dir/main.cpp.o.requires

.PHONY : CMakeFiles/nibbler.dir/requires

CMakeFiles/nibbler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nibbler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nibbler.dir/clean

CMakeFiles/nibbler.dir/depend:
	cd /home/sassyrog/Desktop/Nibbler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sassyrog/Desktop/Nibbler /home/sassyrog/Desktop/Nibbler /home/sassyrog/Desktop/Nibbler /home/sassyrog/Desktop/Nibbler /home/sassyrog/Desktop/Nibbler/CMakeFiles/nibbler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nibbler.dir/depend

