# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.0.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.0.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build

# Include any dependencies generated for this target.
include src/specfun/CMakeFiles/specfun.dir/depend.make

# Include the progress variables for this target.
include src/specfun/CMakeFiles/specfun.dir/progress.make

# Include the compile flags for this target's objects.
include src/specfun/CMakeFiles/specfun.dir/flags.make

src/specfun/CMakeFiles/specfun.dir/specfun.c.obj: src/specfun/CMakeFiles/specfun.dir/flags.make
src/specfun/CMakeFiles/specfun.dir/specfun.c.obj: src/specfun/CMakeFiles/specfun.dir/includes_C.rsp
src/specfun/CMakeFiles/specfun.dir/specfun.c.obj: ../src/specfun/specfun.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/specfun/CMakeFiles/specfun.dir/specfun.c.obj"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/specfun.dir/specfun.c.obj   -c /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/specfun.c

src/specfun/CMakeFiles/specfun.dir/specfun.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/specfun.dir/specfun.c.i"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/specfun.c > CMakeFiles/specfun.dir/specfun.c.i

src/specfun/CMakeFiles/specfun.dir/specfun.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/specfun.dir/specfun.c.s"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/specfun.c -o CMakeFiles/specfun.dir/specfun.c.s

src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.requires:
.PHONY : src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.requires

src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.provides: src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.requires
	$(MAKE) -f src/specfun/CMakeFiles/specfun.dir/build.make src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.provides.build
.PHONY : src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.provides

src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.provides.build: src/specfun/CMakeFiles/specfun.dir/specfun.c.obj

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj: src/specfun/CMakeFiles/specfun.dir/flags.make
src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj: src/specfun/CMakeFiles/specfun.dir/includes_C.rsp
src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj: ../src/specfun/hyperg_u.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/specfun.dir/hyperg_u.c.obj   -c /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/hyperg_u.c

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/specfun.dir/hyperg_u.c.i"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/hyperg_u.c > CMakeFiles/specfun.dir/hyperg_u.c.i

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/specfun.dir/hyperg_u.c.s"
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && /usr/local/mingw32/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun/hyperg_u.c -o CMakeFiles/specfun.dir/hyperg_u.c.s

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.requires:
.PHONY : src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.requires

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.provides: src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.requires
	$(MAKE) -f src/specfun/CMakeFiles/specfun.dir/build.make src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.provides.build
.PHONY : src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.provides

src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.provides.build: src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj

specfun: src/specfun/CMakeFiles/specfun.dir/specfun.c.obj
specfun: src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj
specfun: src/specfun/CMakeFiles/specfun.dir/build.make
.PHONY : specfun

# Rule to build all files generated by this target.
src/specfun/CMakeFiles/specfun.dir/build: specfun
.PHONY : src/specfun/CMakeFiles/specfun.dir/build

src/specfun/CMakeFiles/specfun.dir/requires: src/specfun/CMakeFiles/specfun.dir/specfun.c.obj.requires
src/specfun/CMakeFiles/specfun.dir/requires: src/specfun/CMakeFiles/specfun.dir/hyperg_u.c.obj.requires
.PHONY : src/specfun/CMakeFiles/specfun.dir/requires

src/specfun/CMakeFiles/specfun.dir/clean:
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun && $(CMAKE_COMMAND) -P CMakeFiles/specfun.dir/cmake_clean.cmake
.PHONY : src/specfun/CMakeFiles/specfun.dir/clean

src/specfun/CMakeFiles/specfun.dir/depend:
	cd /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1 /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/src/specfun /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun /Users/jl/tmp/pnl-20140722/pnl-win32-1.7.1/build/src/specfun/CMakeFiles/specfun.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/specfun/CMakeFiles/specfun.dir/depend

