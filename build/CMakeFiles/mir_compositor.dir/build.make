# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/cmake/1417/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1417/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/CLionProjects/mir-compositor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/CLionProjects/mir-compositor/build

# Include any dependencies generated for this target.
include CMakeFiles/mir_compositor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mir_compositor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mir_compositor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mir_compositor.dir/flags.make

CMakeFiles/mir_compositor.dir/src/main.cpp.o: CMakeFiles/mir_compositor.dir/flags.make
CMakeFiles/mir_compositor.dir/src/main.cpp.o: /home/ubuntu/CLionProjects/mir-compositor/src/main.cpp
CMakeFiles/mir_compositor.dir/src/main.cpp.o: CMakeFiles/mir_compositor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/CLionProjects/mir-compositor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mir_compositor.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mir_compositor.dir/src/main.cpp.o -MF CMakeFiles/mir_compositor.dir/src/main.cpp.o.d -o CMakeFiles/mir_compositor.dir/src/main.cpp.o -c /home/ubuntu/CLionProjects/mir-compositor/src/main.cpp

CMakeFiles/mir_compositor.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mir_compositor.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/CLionProjects/mir-compositor/src/main.cpp > CMakeFiles/mir_compositor.dir/src/main.cpp.i

CMakeFiles/mir_compositor.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mir_compositor.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/CLionProjects/mir-compositor/src/main.cpp -o CMakeFiles/mir_compositor.dir/src/main.cpp.s

CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o: CMakeFiles/mir_compositor.dir/flags.make
CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o: /home/ubuntu/CLionProjects/mir-compositor/src/shell_manager.cpp
CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o: CMakeFiles/mir_compositor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ubuntu/CLionProjects/mir-compositor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o -MF CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o.d -o CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o -c /home/ubuntu/CLionProjects/mir-compositor/src/shell_manager.cpp

CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/CLionProjects/mir-compositor/src/shell_manager.cpp > CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.i

CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/CLionProjects/mir-compositor/src/shell_manager.cpp -o CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.s

# Object files for target mir_compositor
mir_compositor_OBJECTS = \
"CMakeFiles/mir_compositor.dir/src/main.cpp.o" \
"CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o"

# External object files for target mir_compositor
mir_compositor_EXTERNAL_OBJECTS =

mir_compositor: CMakeFiles/mir_compositor.dir/src/main.cpp.o
mir_compositor: CMakeFiles/mir_compositor.dir/src/shell_manager.cpp.o
mir_compositor: CMakeFiles/mir_compositor.dir/build.make
mir_compositor: CMakeFiles/mir_compositor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ubuntu/CLionProjects/mir-compositor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable mir_compositor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mir_compositor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mir_compositor.dir/build: mir_compositor
.PHONY : CMakeFiles/mir_compositor.dir/build

CMakeFiles/mir_compositor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mir_compositor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mir_compositor.dir/clean

CMakeFiles/mir_compositor.dir/depend:
	cd /home/ubuntu/CLionProjects/mir-compositor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/CLionProjects/mir-compositor /home/ubuntu/CLionProjects/mir-compositor /home/ubuntu/CLionProjects/mir-compositor/build /home/ubuntu/CLionProjects/mir-compositor/build /home/ubuntu/CLionProjects/mir-compositor/build/CMakeFiles/mir_compositor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mir_compositor.dir/depend

