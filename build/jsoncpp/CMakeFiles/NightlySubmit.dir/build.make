# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /data/home/user00/code/cppserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/home/user00/code/cppserver/build

# Utility rule file for NightlySubmit.

# Include any custom commands dependencies for this target.
include jsoncpp/CMakeFiles/NightlySubmit.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/CMakeFiles/NightlySubmit.dir/progress.make

jsoncpp/CMakeFiles/NightlySubmit:
	cd /data/home/user00/code/cppserver/build/jsoncpp && /usr/bin/ctest -D NightlySubmit

NightlySubmit: jsoncpp/CMakeFiles/NightlySubmit
NightlySubmit: jsoncpp/CMakeFiles/NightlySubmit.dir/build.make
.PHONY : NightlySubmit

# Rule to build all files generated by this target.
jsoncpp/CMakeFiles/NightlySubmit.dir/build: NightlySubmit
.PHONY : jsoncpp/CMakeFiles/NightlySubmit.dir/build

jsoncpp/CMakeFiles/NightlySubmit.dir/clean:
	cd /data/home/user00/code/cppserver/build/jsoncpp && $(CMAKE_COMMAND) -P CMakeFiles/NightlySubmit.dir/cmake_clean.cmake
.PHONY : jsoncpp/CMakeFiles/NightlySubmit.dir/clean

jsoncpp/CMakeFiles/NightlySubmit.dir/depend:
	cd /data/home/user00/code/cppserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/home/user00/code/cppserver /data/home/user00/code/cppserver/jsoncpp /data/home/user00/code/cppserver/build /data/home/user00/code/cppserver/build/jsoncpp /data/home/user00/code/cppserver/build/jsoncpp/CMakeFiles/NightlySubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/CMakeFiles/NightlySubmit.dir/depend
