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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/monitors.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/monitors.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/monitors.dir/flags.make

tests/CMakeFiles/monitors.dir/monitors.c.o: tests/CMakeFiles/monitors.dir/flags.make
tests/CMakeFiles/monitors.dir/monitors.c.o: ../tests/monitors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/monitors.dir/monitors.c.o"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitors.dir/monitors.c.o   -c /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/tests/monitors.c

tests/CMakeFiles/monitors.dir/monitors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/monitors.c.i"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/tests/monitors.c > CMakeFiles/monitors.dir/monitors.c.i

tests/CMakeFiles/monitors.dir/monitors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/monitors.c.s"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/tests/monitors.c -o CMakeFiles/monitors.dir/monitors.c.s

tests/CMakeFiles/monitors.dir/monitors.c.o.requires:

.PHONY : tests/CMakeFiles/monitors.dir/monitors.c.o.requires

tests/CMakeFiles/monitors.dir/monitors.c.o.provides: tests/CMakeFiles/monitors.dir/monitors.c.o.requires
	$(MAKE) -f tests/CMakeFiles/monitors.dir/build.make tests/CMakeFiles/monitors.dir/monitors.c.o.provides.build
.PHONY : tests/CMakeFiles/monitors.dir/monitors.c.o.provides

tests/CMakeFiles/monitors.dir/monitors.c.o.provides.build: tests/CMakeFiles/monitors.dir/monitors.c.o


tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o: tests/CMakeFiles/monitors.dir/flags.make
tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o: ../deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monitors.dir/__/deps/getopt.c.o   -c /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/getopt.c

tests/CMakeFiles/monitors.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monitors.dir/__/deps/getopt.c.i"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/getopt.c > CMakeFiles/monitors.dir/__/deps/getopt.c.i

tests/CMakeFiles/monitors.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monitors.dir/__/deps/getopt.c.s"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/getopt.c -o CMakeFiles/monitors.dir/__/deps/getopt.c.s

tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.requires:

.PHONY : tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.requires

tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.provides: tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.requires
	$(MAKE) -f tests/CMakeFiles/monitors.dir/build.make tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.provides.build
.PHONY : tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.provides

tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.provides.build: tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o


# Object files for target monitors
monitors_OBJECTS = \
"CMakeFiles/monitors.dir/monitors.c.o" \
"CMakeFiles/monitors.dir/__/deps/getopt.c.o"

# External object files for target monitors
monitors_EXTERNAL_OBJECTS =

tests/monitors: tests/CMakeFiles/monitors.dir/monitors.c.o
tests/monitors: tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o
tests/monitors: tests/CMakeFiles/monitors.dir/build.make
tests/monitors: src/libglfw3.a
tests/monitors: tests/CMakeFiles/monitors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable monitors"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monitors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/monitors.dir/build: tests/monitors

.PHONY : tests/CMakeFiles/monitors.dir/build

tests/CMakeFiles/monitors.dir/requires: tests/CMakeFiles/monitors.dir/monitors.c.o.requires
tests/CMakeFiles/monitors.dir/requires: tests/CMakeFiles/monitors.dir/__/deps/getopt.c.o.requires

.PHONY : tests/CMakeFiles/monitors.dir/requires

tests/CMakeFiles/monitors.dir/clean:
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/monitors.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/monitors.dir/clean

tests/CMakeFiles/monitors.dir/depend:
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1 /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/tests /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/tests/CMakeFiles/monitors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/monitors.dir/depend

