# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lahwaacz/Dropbox/pg/C++/wmfs-statusbar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lahwaacz/Dropbox/pg/C++/wmfs-statusbar

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lahwaacz/Dropbox/pg/C++/wmfs-statusbar/CMakeFiles /home/lahwaacz/Dropbox/pg/C++/wmfs-statusbar/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lahwaacz/Dropbox/pg/C++/wmfs-statusbar/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named status

# Build rule for target.
status: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 status
.PHONY : status

# fast build rule for target.
status/fast:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/build
.PHONY : status/fast

src/PluginBattery.o: src/PluginBattery.cpp.o
.PHONY : src/PluginBattery.o

# target to build an object file
src/PluginBattery.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginBattery.cpp.o
.PHONY : src/PluginBattery.cpp.o

src/PluginBattery.i: src/PluginBattery.cpp.i
.PHONY : src/PluginBattery.i

# target to preprocess a source file
src/PluginBattery.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginBattery.cpp.i
.PHONY : src/PluginBattery.cpp.i

src/PluginBattery.s: src/PluginBattery.cpp.s
.PHONY : src/PluginBattery.s

# target to generate assembly for a file
src/PluginBattery.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginBattery.cpp.s
.PHONY : src/PluginBattery.cpp.s

src/PluginCPU.o: src/PluginCPU.cpp.o
.PHONY : src/PluginCPU.o

# target to build an object file
src/PluginCPU.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginCPU.cpp.o
.PHONY : src/PluginCPU.cpp.o

src/PluginCPU.i: src/PluginCPU.cpp.i
.PHONY : src/PluginCPU.i

# target to preprocess a source file
src/PluginCPU.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginCPU.cpp.i
.PHONY : src/PluginCPU.cpp.i

src/PluginCPU.s: src/PluginCPU.cpp.s
.PHONY : src/PluginCPU.s

# target to generate assembly for a file
src/PluginCPU.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginCPU.cpp.s
.PHONY : src/PluginCPU.cpp.s

src/PluginDate.o: src/PluginDate.cpp.o
.PHONY : src/PluginDate.o

# target to build an object file
src/PluginDate.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginDate.cpp.o
.PHONY : src/PluginDate.cpp.o

src/PluginDate.i: src/PluginDate.cpp.i
.PHONY : src/PluginDate.i

# target to preprocess a source file
src/PluginDate.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginDate.cpp.i
.PHONY : src/PluginDate.cpp.i

src/PluginDate.s: src/PluginDate.cpp.s
.PHONY : src/PluginDate.s

# target to generate assembly for a file
src/PluginDate.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginDate.cpp.s
.PHONY : src/PluginDate.cpp.s

src/PluginEssid.o: src/PluginEssid.cpp.o
.PHONY : src/PluginEssid.o

# target to build an object file
src/PluginEssid.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginEssid.cpp.o
.PHONY : src/PluginEssid.cpp.o

src/PluginEssid.i: src/PluginEssid.cpp.i
.PHONY : src/PluginEssid.i

# target to preprocess a source file
src/PluginEssid.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginEssid.cpp.i
.PHONY : src/PluginEssid.cpp.i

src/PluginEssid.s: src/PluginEssid.cpp.s
.PHONY : src/PluginEssid.s

# target to generate assembly for a file
src/PluginEssid.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginEssid.cpp.s
.PHONY : src/PluginEssid.cpp.s

src/PluginIP.o: src/PluginIP.cpp.o
.PHONY : src/PluginIP.o

# target to build an object file
src/PluginIP.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginIP.cpp.o
.PHONY : src/PluginIP.cpp.o

src/PluginIP.i: src/PluginIP.cpp.i
.PHONY : src/PluginIP.i

# target to preprocess a source file
src/PluginIP.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginIP.cpp.i
.PHONY : src/PluginIP.cpp.i

src/PluginIP.s: src/PluginIP.cpp.s
.PHONY : src/PluginIP.s

# target to generate assembly for a file
src/PluginIP.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginIP.cpp.s
.PHONY : src/PluginIP.cpp.s

src/PluginMPD.o: src/PluginMPD.cpp.o
.PHONY : src/PluginMPD.o

# target to build an object file
src/PluginMPD.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginMPD.cpp.o
.PHONY : src/PluginMPD.cpp.o

src/PluginMPD.i: src/PluginMPD.cpp.i
.PHONY : src/PluginMPD.i

# target to preprocess a source file
src/PluginMPD.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginMPD.cpp.i
.PHONY : src/PluginMPD.cpp.i

src/PluginMPD.s: src/PluginMPD.cpp.s
.PHONY : src/PluginMPD.s

# target to generate assembly for a file
src/PluginMPD.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginMPD.cpp.s
.PHONY : src/PluginMPD.cpp.s

src/PluginNetwork.o: src/PluginNetwork.cpp.o
.PHONY : src/PluginNetwork.o

# target to build an object file
src/PluginNetwork.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginNetwork.cpp.o
.PHONY : src/PluginNetwork.cpp.o

src/PluginNetwork.i: src/PluginNetwork.cpp.i
.PHONY : src/PluginNetwork.i

# target to preprocess a source file
src/PluginNetwork.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginNetwork.cpp.i
.PHONY : src/PluginNetwork.cpp.i

src/PluginNetwork.s: src/PluginNetwork.cpp.s
.PHONY : src/PluginNetwork.s

# target to generate assembly for a file
src/PluginNetwork.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginNetwork.cpp.s
.PHONY : src/PluginNetwork.cpp.s

src/PluginRAM.o: src/PluginRAM.cpp.o
.PHONY : src/PluginRAM.o

# target to build an object file
src/PluginRAM.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginRAM.cpp.o
.PHONY : src/PluginRAM.cpp.o

src/PluginRAM.i: src/PluginRAM.cpp.i
.PHONY : src/PluginRAM.i

# target to preprocess a source file
src/PluginRAM.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginRAM.cpp.i
.PHONY : src/PluginRAM.cpp.i

src/PluginRAM.s: src/PluginRAM.cpp.s
.PHONY : src/PluginRAM.s

# target to generate assembly for a file
src/PluginRAM.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginRAM.cpp.s
.PHONY : src/PluginRAM.cpp.s

src/PluginVolume.o: src/PluginVolume.cpp.o
.PHONY : src/PluginVolume.o

# target to build an object file
src/PluginVolume.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginVolume.cpp.o
.PHONY : src/PluginVolume.cpp.o

src/PluginVolume.i: src/PluginVolume.cpp.i
.PHONY : src/PluginVolume.i

# target to preprocess a source file
src/PluginVolume.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginVolume.cpp.i
.PHONY : src/PluginVolume.cpp.i

src/PluginVolume.s: src/PluginVolume.cpp.s
.PHONY : src/PluginVolume.s

# target to generate assembly for a file
src/PluginVolume.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/PluginVolume.cpp.s
.PHONY : src/PluginVolume.cpp.s

src/Xstatus.o: src/Xstatus.cpp.o
.PHONY : src/Xstatus.o

# target to build an object file
src/Xstatus.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/Xstatus.cpp.o
.PHONY : src/Xstatus.cpp.o

src/Xstatus.i: src/Xstatus.cpp.i
.PHONY : src/Xstatus.i

# target to preprocess a source file
src/Xstatus.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/Xstatus.cpp.i
.PHONY : src/Xstatus.cpp.i

src/Xstatus.s: src/Xstatus.cpp.s
.PHONY : src/Xstatus.s

# target to generate assembly for a file
src/Xstatus.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/Xstatus.cpp.s
.PHONY : src/Xstatus.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/pulse.o: src/pulse.cpp.o
.PHONY : src/pulse.o

# target to build an object file
src/pulse.cpp.o:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/pulse.cpp.o
.PHONY : src/pulse.cpp.o

src/pulse.i: src/pulse.cpp.i
.PHONY : src/pulse.i

# target to preprocess a source file
src/pulse.cpp.i:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/pulse.cpp.i
.PHONY : src/pulse.cpp.i

src/pulse.s: src/pulse.cpp.s
.PHONY : src/pulse.s

# target to generate assembly for a file
src/pulse.cpp.s:
	$(MAKE) -f CMakeFiles/status.dir/build.make CMakeFiles/status.dir/src/pulse.cpp.s
.PHONY : src/pulse.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... status"
	@echo "... src/PluginBattery.o"
	@echo "... src/PluginBattery.i"
	@echo "... src/PluginBattery.s"
	@echo "... src/PluginCPU.o"
	@echo "... src/PluginCPU.i"
	@echo "... src/PluginCPU.s"
	@echo "... src/PluginDate.o"
	@echo "... src/PluginDate.i"
	@echo "... src/PluginDate.s"
	@echo "... src/PluginEssid.o"
	@echo "... src/PluginEssid.i"
	@echo "... src/PluginEssid.s"
	@echo "... src/PluginIP.o"
	@echo "... src/PluginIP.i"
	@echo "... src/PluginIP.s"
	@echo "... src/PluginMPD.o"
	@echo "... src/PluginMPD.i"
	@echo "... src/PluginMPD.s"
	@echo "... src/PluginNetwork.o"
	@echo "... src/PluginNetwork.i"
	@echo "... src/PluginNetwork.s"
	@echo "... src/PluginRAM.o"
	@echo "... src/PluginRAM.i"
	@echo "... src/PluginRAM.s"
	@echo "... src/PluginVolume.o"
	@echo "... src/PluginVolume.i"
	@echo "... src/PluginVolume.s"
	@echo "... src/Xstatus.o"
	@echo "... src/Xstatus.i"
	@echo "... src/Xstatus.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/pulse.o"
	@echo "... src/pulse.i"
	@echo "... src/pulse.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

