# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /media/knox/ExtDrive/Dev/Dumicola/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/knox/ExtDrive/Dev/Dumicola/src

# Include any dependencies generated for this target.
include dumidesk/CMakeFiles/DUMIDESK.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include dumidesk/CMakeFiles/DUMIDESK.dir/compiler_depend.make

# Include the progress variables for this target.
include dumidesk/CMakeFiles/DUMIDESK.dir/progress.make

# Include the compile flags for this target's objects.
include dumidesk/CMakeFiles/DUMIDESK.dir/flags.make

dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o: dumidesk/CMakeFiles/DUMIDESK.dir/flags.make
dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o: dumidesk/dumidesk.cpp
dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o: dumidesk/CMakeFiles/DUMIDESK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/knox/ExtDrive/Dev/Dumicola/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o -MF CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o.d -o CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o -c /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk/dumidesk.cpp

dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DUMIDESK.dir/dumidesk.cpp.i"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk/dumidesk.cpp > CMakeFiles/DUMIDESK.dir/dumidesk.cpp.i

dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DUMIDESK.dir/dumidesk.cpp.s"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk/dumidesk.cpp -o CMakeFiles/DUMIDESK.dir/dumidesk.cpp.s

dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o: dumidesk/CMakeFiles/DUMIDESK.dir/flags.make
dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o: dumicommon/dumicommon.cpp
dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o: dumidesk/CMakeFiles/DUMIDESK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/media/knox/ExtDrive/Dev/Dumicola/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o -MF CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o.d -o CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o -c /media/knox/ExtDrive/Dev/Dumicola/src/dumicommon/dumicommon.cpp

dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.i"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/knox/ExtDrive/Dev/Dumicola/src/dumicommon/dumicommon.cpp > CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.i

dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.s"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/knox/ExtDrive/Dev/Dumicola/src/dumicommon/dumicommon.cpp -o CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.s

# Object files for target DUMIDESK
DUMIDESK_OBJECTS = \
"CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o" \
"CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o"

# External object files for target DUMIDESK
DUMIDESK_EXTERNAL_OBJECTS =

/media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK: dumidesk/CMakeFiles/DUMIDESK.dir/dumidesk.cpp.o
/media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK: dumidesk/CMakeFiles/DUMIDESK.dir/__/dumicommon/dumicommon.cpp.o
/media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK: dumidesk/CMakeFiles/DUMIDESK.dir/build.make
/media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK: /media/knox/ExtDrive/Dev/Dumicola/src../build/libDUMICOMMON.so
/media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK: dumidesk/CMakeFiles/DUMIDESK.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/media/knox/ExtDrive/Dev/Dumicola/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK"
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DUMIDESK.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
dumidesk/CMakeFiles/DUMIDESK.dir/build: /media/knox/ExtDrive/Dev/Dumicola/src../build/DUMIDESK
.PHONY : dumidesk/CMakeFiles/DUMIDESK.dir/build

dumidesk/CMakeFiles/DUMIDESK.dir/clean:
	cd /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk && $(CMAKE_COMMAND) -P CMakeFiles/DUMIDESK.dir/cmake_clean.cmake
.PHONY : dumidesk/CMakeFiles/DUMIDESK.dir/clean

dumidesk/CMakeFiles/DUMIDESK.dir/depend:
	cd /media/knox/ExtDrive/Dev/Dumicola/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/knox/ExtDrive/Dev/Dumicola/src /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk /media/knox/ExtDrive/Dev/Dumicola/src /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk /media/knox/ExtDrive/Dev/Dumicola/src/dumidesk/CMakeFiles/DUMIDESK.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : dumidesk/CMakeFiles/DUMIDESK.dir/depend

