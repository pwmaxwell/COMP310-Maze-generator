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
CMAKE_SOURCE_DIR = /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment

# Include any dependencies generated for this target.
include CMakeFiles/MazeSolver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MazeSolver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MazeSolver.dir/flags.make

CMakeFiles/MazeSolver.dir/MazeSolver.c.o: CMakeFiles/MazeSolver.dir/flags.make
CMakeFiles/MazeSolver.dir/MazeSolver.c.o: MazeSolver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MazeSolver.dir/MazeSolver.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MazeSolver.dir/MazeSolver.c.o   -c /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/MazeSolver.c

CMakeFiles/MazeSolver.dir/MazeSolver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MazeSolver.dir/MazeSolver.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/MazeSolver.c > CMakeFiles/MazeSolver.dir/MazeSolver.c.i

CMakeFiles/MazeSolver.dir/MazeSolver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MazeSolver.dir/MazeSolver.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/MazeSolver.c -o CMakeFiles/MazeSolver.dir/MazeSolver.c.s

CMakeFiles/MazeSolver.dir/MazeSolver.c.o.requires:

.PHONY : CMakeFiles/MazeSolver.dir/MazeSolver.c.o.requires

CMakeFiles/MazeSolver.dir/MazeSolver.c.o.provides: CMakeFiles/MazeSolver.dir/MazeSolver.c.o.requires
	$(MAKE) -f CMakeFiles/MazeSolver.dir/build.make CMakeFiles/MazeSolver.dir/MazeSolver.c.o.provides.build
.PHONY : CMakeFiles/MazeSolver.dir/MazeSolver.c.o.provides

CMakeFiles/MazeSolver.dir/MazeSolver.c.o.provides.build: CMakeFiles/MazeSolver.dir/MazeSolver.c.o


# Object files for target MazeSolver
MazeSolver_OBJECTS = \
"CMakeFiles/MazeSolver.dir/MazeSolver.c.o"

# External object files for target MazeSolver
MazeSolver_EXTERNAL_OBJECTS =

bin/MazeSolver: CMakeFiles/MazeSolver.dir/MazeSolver.c.o
bin/MazeSolver: CMakeFiles/MazeSolver.dir/build.make
bin/MazeSolver: CMakeFiles/MazeSolver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/MazeSolver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MazeSolver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MazeSolver.dir/build: bin/MazeSolver

.PHONY : CMakeFiles/MazeSolver.dir/build

CMakeFiles/MazeSolver.dir/requires: CMakeFiles/MazeSolver.dir/MazeSolver.c.o.requires

.PHONY : CMakeFiles/MazeSolver.dir/requires

CMakeFiles/MazeSolver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MazeSolver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MazeSolver.dir/clean

CMakeFiles/MazeSolver.dir/depend:
	cd /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment /mnt/c/users/pwmax/Desktop/Assignment1Comp310/Assignment/CMakeFiles/MazeSolver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MazeSolver.dir/depend

