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

# Include any dependencies generated for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/compiler_depend.make

# Include the progress variables for this target.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/progress.make

# Include the compile flags for this target's objects.
include jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/flags.make

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o: ../jsoncpp/src/lib_json/json_reader.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/user00/code/cppserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o -MF CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o.d -o CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o -c /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_reader.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_object.dir/json_reader.cpp.i"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_reader.cpp > CMakeFiles/jsoncpp_object.dir/json_reader.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_object.dir/json_reader.cpp.s"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_reader.cpp -o CMakeFiles/jsoncpp_object.dir/json_reader.cpp.s

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o: ../jsoncpp/src/lib_json/json_value.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/user00/code/cppserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o -MF CMakeFiles/jsoncpp_object.dir/json_value.cpp.o.d -o CMakeFiles/jsoncpp_object.dir/json_value.cpp.o -c /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_value.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_object.dir/json_value.cpp.i"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_value.cpp > CMakeFiles/jsoncpp_object.dir/json_value.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_object.dir/json_value.cpp.s"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_value.cpp -o CMakeFiles/jsoncpp_object.dir/json_value.cpp.s

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/flags.make
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o: ../jsoncpp/src/lib_json/json_writer.cpp
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/user00/code/cppserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o -MF CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o.d -o CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o -c /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_writer.cpp

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jsoncpp_object.dir/json_writer.cpp.i"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_writer.cpp > CMakeFiles/jsoncpp_object.dir/json_writer.cpp.i

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jsoncpp_object.dir/json_writer.cpp.s"
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/user00/code/cppserver/jsoncpp/src/lib_json/json_writer.cpp -o CMakeFiles/jsoncpp_object.dir/json_writer.cpp.s

jsoncpp_object: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_reader.cpp.o
jsoncpp_object: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_value.cpp.o
jsoncpp_object: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/json_writer.cpp.o
jsoncpp_object: jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/build.make
.PHONY : jsoncpp_object

# Rule to build all files generated by this target.
jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/build: jsoncpp_object
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/build

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/clean:
	cd /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json && $(CMAKE_COMMAND) -P CMakeFiles/jsoncpp_object.dir/cmake_clean.cmake
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/clean

jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/depend:
	cd /data/home/user00/code/cppserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/home/user00/code/cppserver /data/home/user00/code/cppserver/jsoncpp/src/lib_json /data/home/user00/code/cppserver/build /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json /data/home/user00/code/cppserver/build/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jsoncpp/src/lib_json/CMakeFiles/jsoncpp_object.dir/depend

