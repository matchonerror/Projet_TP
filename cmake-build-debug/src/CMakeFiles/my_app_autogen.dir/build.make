# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tranhan/CLionProjects/Projet_TP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug

# Utility rule file for my_app_autogen.

# Include any custom commands dependencies for this target.
include src/CMakeFiles/my_app_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/my_app_autogen.dir/progress.make

src/CMakeFiles/my_app_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target my_app"
	cd /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/src && /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E cmake_autogen /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/src/CMakeFiles/my_app_autogen.dir/AutogenInfo.json Debug

my_app_autogen: src/CMakeFiles/my_app_autogen
my_app_autogen: src/CMakeFiles/my_app_autogen.dir/build.make
.PHONY : my_app_autogen

# Rule to build all files generated by this target.
src/CMakeFiles/my_app_autogen.dir/build: my_app_autogen
.PHONY : src/CMakeFiles/my_app_autogen.dir/build

src/CMakeFiles/my_app_autogen.dir/clean:
	cd /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/my_app_autogen.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/my_app_autogen.dir/clean

src/CMakeFiles/my_app_autogen.dir/depend:
	cd /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tranhan/CLionProjects/Projet_TP /Users/tranhan/CLionProjects/Projet_TP/src /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/src /Users/tranhan/CLionProjects/Projet_TP/cmake-build-debug/src/CMakeFiles/my_app_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/my_app_autogen.dir/depend

