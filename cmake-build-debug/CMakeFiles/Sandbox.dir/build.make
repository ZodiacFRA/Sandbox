# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /home/seb/bin/cmake-3.13.1-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/seb/bin/cmake-3.13.1-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seb/Sandbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seb/Sandbox/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Sandbox.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Sandbox.dir/flags.make

CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o: ../ecs/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o -c /home/seb/Sandbox/ecs/Entity.cpp

CMakeFiles/Sandbox.dir/ecs/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/ecs/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/ecs/Entity.cpp > CMakeFiles/Sandbox.dir/ecs/Entity.cpp.i

CMakeFiles/Sandbox.dir/ecs/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/ecs/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/ecs/Entity.cpp -o CMakeFiles/Sandbox.dir/ecs/Entity.cpp.s

CMakeFiles/Sandbox.dir/ecs/Time.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/ecs/Time.cpp.o: ../ecs/Time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Sandbox.dir/ecs/Time.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/ecs/Time.cpp.o -c /home/seb/Sandbox/ecs/Time.cpp

CMakeFiles/Sandbox.dir/ecs/Time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/ecs/Time.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/ecs/Time.cpp > CMakeFiles/Sandbox.dir/ecs/Time.cpp.i

CMakeFiles/Sandbox.dir/ecs/Time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/ecs/Time.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/ecs/Time.cpp -o CMakeFiles/Sandbox.dir/ecs/Time.cpp.s

CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o: ../ecs/TimedEvent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o -c /home/seb/Sandbox/ecs/TimedEvent.cpp

CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/ecs/TimedEvent.cpp > CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.i

CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/ecs/TimedEvent.cpp -o CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.s

CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o: ../ecs/TimedEventAdmin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o -c /home/seb/Sandbox/ecs/TimedEventAdmin.cpp

CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/ecs/TimedEventAdmin.cpp > CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.i

CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/ecs/TimedEventAdmin.cpp -o CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.s

CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o: ../Workers/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o -c /home/seb/Sandbox/Workers/ThreadPool.cpp

CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/Workers/ThreadPool.cpp > CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.i

CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/Workers/ThreadPool.cpp -o CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.s

CMakeFiles/Sandbox.dir/Main.cpp.o: CMakeFiles/Sandbox.dir/flags.make
CMakeFiles/Sandbox.dir/Main.cpp.o: ../Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Sandbox.dir/Main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Sandbox.dir/Main.cpp.o -c /home/seb/Sandbox/Main.cpp

CMakeFiles/Sandbox.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Sandbox.dir/Main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seb/Sandbox/Main.cpp > CMakeFiles/Sandbox.dir/Main.cpp.i

CMakeFiles/Sandbox.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Sandbox.dir/Main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seb/Sandbox/Main.cpp -o CMakeFiles/Sandbox.dir/Main.cpp.s

# Object files for target Sandbox
Sandbox_OBJECTS = \
"CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o" \
"CMakeFiles/Sandbox.dir/ecs/Time.cpp.o" \
"CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o" \
"CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o" \
"CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o" \
"CMakeFiles/Sandbox.dir/Main.cpp.o"

# External object files for target Sandbox
Sandbox_EXTERNAL_OBJECTS =

Sandbox: CMakeFiles/Sandbox.dir/ecs/Entity.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/ecs/Time.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/ecs/TimedEvent.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/ecs/TimedEventAdmin.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/Workers/ThreadPool.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/Main.cpp.o
Sandbox: CMakeFiles/Sandbox.dir/build.make
Sandbox: CMakeFiles/Sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seb/Sandbox/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Sandbox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Sandbox.dir/build: Sandbox

.PHONY : CMakeFiles/Sandbox.dir/build

CMakeFiles/Sandbox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Sandbox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Sandbox.dir/clean

CMakeFiles/Sandbox.dir/depend:
	cd /home/seb/Sandbox/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seb/Sandbox /home/seb/Sandbox /home/seb/Sandbox/cmake-build-debug /home/seb/Sandbox/cmake-build-debug /home/seb/Sandbox/cmake-build-debug/CMakeFiles/Sandbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Sandbox.dir/depend

