# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\OneDrive\Desktop\NetSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\OneDrive\Desktop\NetSim\cmake-build-debug

# Include any dependencies generated for this target.
include googletest-main/CMakeFiles/polprodukty_wezly.dir/depend.make

# Include the progress variables for this target.
include googletest-main/CMakeFiles/polprodukty_wezly.dir/progress.make

# Include the compile flags for this target's objects.
include googletest-main/CMakeFiles/polprodukty_wezly.dir/flags.make

googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.obj: googletest-main/CMakeFiles/polprodukty_wezly.dir/flags.make
googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.obj: googletest-main/CMakeFiles/polprodukty_wezly.dir/includes_CXX.rsp
googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.obj: ../polprodukty_wezly/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\OneDrive\Desktop\NetSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.obj"
	cd /d D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\polprodukty_wezly.dir\main.cpp.obj -c D:\OneDrive\Desktop\NetSim\polprodukty_wezly\main.cpp

googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/polprodukty_wezly.dir/main.cpp.i"
	cd /d D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\OneDrive\Desktop\NetSim\polprodukty_wezly\main.cpp > CMakeFiles\polprodukty_wezly.dir\main.cpp.i

googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/polprodukty_wezly.dir/main.cpp.s"
	cd /d D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\OneDrive\Desktop\NetSim\polprodukty_wezly\main.cpp -o CMakeFiles\polprodukty_wezly.dir\main.cpp.s

# Object files for target polprodukty_wezly
polprodukty_wezly_OBJECTS = \
"CMakeFiles/polprodukty_wezly.dir/main.cpp.obj"

# External object files for target polprodukty_wezly
polprodukty_wezly_EXTERNAL_OBJECTS =

googletest-main/polprodukty_wezly.exe: googletest-main/CMakeFiles/polprodukty_wezly.dir/main.cpp.obj
googletest-main/polprodukty_wezly.exe: googletest-main/CMakeFiles/polprodukty_wezly.dir/build.make
googletest-main/polprodukty_wezly.exe: googletest-main/CMakeFiles/polprodukty_wezly.dir/linklibs.rsp
googletest-main/polprodukty_wezly.exe: googletest-main/CMakeFiles/polprodukty_wezly.dir/objects1.rsp
googletest-main/polprodukty_wezly.exe: googletest-main/CMakeFiles/polprodukty_wezly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\OneDrive\Desktop\NetSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable polprodukty_wezly.exe"
	cd /d D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\polprodukty_wezly.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googletest-main/CMakeFiles/polprodukty_wezly.dir/build: googletest-main/polprodukty_wezly.exe

.PHONY : googletest-main/CMakeFiles/polprodukty_wezly.dir/build

googletest-main/CMakeFiles/polprodukty_wezly.dir/clean:
	cd /d D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main && $(CMAKE_COMMAND) -P CMakeFiles\polprodukty_wezly.dir\cmake_clean.cmake
.PHONY : googletest-main/CMakeFiles/polprodukty_wezly.dir/clean

googletest-main/CMakeFiles/polprodukty_wezly.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\OneDrive\Desktop\NetSim D:\OneDrive\Desktop\NetSim\polprodukty_wezly D:\OneDrive\Desktop\NetSim\cmake-build-debug D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main D:\OneDrive\Desktop\NetSim\cmake-build-debug\googletest-main\CMakeFiles\polprodukty_wezly.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : googletest-main/CMakeFiles/polprodukty_wezly.dir/depend
