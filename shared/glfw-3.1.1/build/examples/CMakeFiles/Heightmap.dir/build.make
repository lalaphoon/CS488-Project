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
include examples/CMakeFiles/Heightmap.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Heightmap.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Heightmap.dir/flags.make

examples/CMakeFiles/Heightmap.dir/heightmap.c.o: examples/CMakeFiles/Heightmap.dir/flags.make
examples/CMakeFiles/Heightmap.dir/heightmap.c.o: ../examples/heightmap.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/Heightmap.dir/heightmap.c.o"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Heightmap.dir/heightmap.c.o   -c /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/examples/heightmap.c

examples/CMakeFiles/Heightmap.dir/heightmap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Heightmap.dir/heightmap.c.i"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/examples/heightmap.c > CMakeFiles/Heightmap.dir/heightmap.c.i

examples/CMakeFiles/Heightmap.dir/heightmap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Heightmap.dir/heightmap.c.s"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/examples/heightmap.c -o CMakeFiles/Heightmap.dir/heightmap.c.s

examples/CMakeFiles/Heightmap.dir/heightmap.c.o.requires:

.PHONY : examples/CMakeFiles/Heightmap.dir/heightmap.c.o.requires

examples/CMakeFiles/Heightmap.dir/heightmap.c.o.provides: examples/CMakeFiles/Heightmap.dir/heightmap.c.o.requires
	$(MAKE) -f examples/CMakeFiles/Heightmap.dir/build.make examples/CMakeFiles/Heightmap.dir/heightmap.c.o.provides.build
.PHONY : examples/CMakeFiles/Heightmap.dir/heightmap.c.o.provides

examples/CMakeFiles/Heightmap.dir/heightmap.c.o.provides.build: examples/CMakeFiles/Heightmap.dir/heightmap.c.o


examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o: examples/CMakeFiles/Heightmap.dir/flags.make
examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o: ../deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Heightmap.dir/__/deps/glad.c.o   -c /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/glad.c

examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Heightmap.dir/__/deps/glad.c.i"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/glad.c > CMakeFiles/Heightmap.dir/__/deps/glad.c.i

examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Heightmap.dir/__/deps/glad.c.s"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/deps/glad.c -o CMakeFiles/Heightmap.dir/__/deps/glad.c.s

examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.requires:

.PHONY : examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.requires

examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.provides: examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.requires
	$(MAKE) -f examples/CMakeFiles/Heightmap.dir/build.make examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.provides.build
.PHONY : examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.provides

examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.provides.build: examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o


# Object files for target Heightmap
Heightmap_OBJECTS = \
"CMakeFiles/Heightmap.dir/heightmap.c.o" \
"CMakeFiles/Heightmap.dir/__/deps/glad.c.o"

# External object files for target Heightmap
Heightmap_EXTERNAL_OBJECTS =

examples/Heightmap.app/Contents/MacOS/Heightmap: examples/CMakeFiles/Heightmap.dir/heightmap.c.o
examples/Heightmap.app/Contents/MacOS/Heightmap: examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o
examples/Heightmap.app/Contents/MacOS/Heightmap: examples/CMakeFiles/Heightmap.dir/build.make
examples/Heightmap.app/Contents/MacOS/Heightmap: src/libglfw3.a
examples/Heightmap.app/Contents/MacOS/Heightmap: examples/CMakeFiles/Heightmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Heightmap.app/Contents/MacOS/Heightmap"
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Heightmap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Heightmap.dir/build: examples/Heightmap.app/Contents/MacOS/Heightmap

.PHONY : examples/CMakeFiles/Heightmap.dir/build

examples/CMakeFiles/Heightmap.dir/requires: examples/CMakeFiles/Heightmap.dir/heightmap.c.o.requires
examples/CMakeFiles/Heightmap.dir/requires: examples/CMakeFiles/Heightmap.dir/__/deps/glad.c.o.requires

.PHONY : examples/CMakeFiles/Heightmap.dir/requires

examples/CMakeFiles/Heightmap.dir/clean:
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Heightmap.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Heightmap.dir/clean

examples/CMakeFiles/Heightmap.dir/depend:
	cd /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1 /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/examples /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples /Users/mengyiluo/Documents/cs488-official/cs488/shared/glfw-3.1.1/build/examples/CMakeFiles/Heightmap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Heightmap.dir/depend

