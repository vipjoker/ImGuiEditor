# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/oleh/Documents/projects/CocosProjects/ClionCocos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug

# Utility rule file for MyGame_PRE_BUILD.

# Include the progress variables for this target.
include CMakeFiles/MyGame_PRE_BUILD.dir/progress.make

MyGame_PRE_BUILD: CMakeFiles/MyGame_PRE_BUILD.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "MyGame_PRE_BUILD ..."
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove_directory /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug/bin/Resources
	/Applications/CLion.app/Contents/bin/cmake/bin/cmake -E copy_directory /Users/oleh/Documents/projects/CocosProjects/ClionCocos/Resources /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug/bin/Resources
.PHONY : MyGame_PRE_BUILD

# Rule to build all files generated by this target.
CMakeFiles/MyGame_PRE_BUILD.dir/build: MyGame_PRE_BUILD

.PHONY : CMakeFiles/MyGame_PRE_BUILD.dir/build

CMakeFiles/MyGame_PRE_BUILD.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyGame_PRE_BUILD.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyGame_PRE_BUILD.dir/clean

CMakeFiles/MyGame_PRE_BUILD.dir/depend:
	cd /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/oleh/Documents/projects/CocosProjects/ClionCocos /Users/oleh/Documents/projects/CocosProjects/ClionCocos /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug /Users/oleh/Documents/projects/CocosProjects/ClionCocos/cmake-build-debug/CMakeFiles/MyGame_PRE_BUILD.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyGame_PRE_BUILD.dir/depend

