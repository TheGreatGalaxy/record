# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/zhenwei-qian/LinuxData/data/capture_window

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/zhenwei-qian/LinuxData/data/capture_window/build

# Include any dependencies generated for this target.
include CMakeFiles/record_by_image.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/record_by_image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/record_by_image.dir/flags.make

CMakeFiles/record_by_image.dir/record_by_image.cpp.o: CMakeFiles/record_by_image.dir/flags.make
CMakeFiles/record_by_image.dir/record_by_image.cpp.o: ../record_by_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/zhenwei-qian/LinuxData/data/capture_window/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/record_by_image.dir/record_by_image.cpp.o"
	/usr/bin/g++-5   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/record_by_image.dir/record_by_image.cpp.o -c /media/zhenwei-qian/LinuxData/data/capture_window/record_by_image.cpp

CMakeFiles/record_by_image.dir/record_by_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/record_by_image.dir/record_by_image.cpp.i"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/zhenwei-qian/LinuxData/data/capture_window/record_by_image.cpp > CMakeFiles/record_by_image.dir/record_by_image.cpp.i

CMakeFiles/record_by_image.dir/record_by_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/record_by_image.dir/record_by_image.cpp.s"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/zhenwei-qian/LinuxData/data/capture_window/record_by_image.cpp -o CMakeFiles/record_by_image.dir/record_by_image.cpp.s

CMakeFiles/record_by_image.dir/record_by_image.cpp.o.requires:

.PHONY : CMakeFiles/record_by_image.dir/record_by_image.cpp.o.requires

CMakeFiles/record_by_image.dir/record_by_image.cpp.o.provides: CMakeFiles/record_by_image.dir/record_by_image.cpp.o.requires
	$(MAKE) -f CMakeFiles/record_by_image.dir/build.make CMakeFiles/record_by_image.dir/record_by_image.cpp.o.provides.build
.PHONY : CMakeFiles/record_by_image.dir/record_by_image.cpp.o.provides

CMakeFiles/record_by_image.dir/record_by_image.cpp.o.provides.build: CMakeFiles/record_by_image.dir/record_by_image.cpp.o


# Object files for target record_by_image
record_by_image_OBJECTS = \
"CMakeFiles/record_by_image.dir/record_by_image.cpp.o"

# External object files for target record_by_image
record_by_image_EXTERNAL_OBJECTS =

record_by_image: CMakeFiles/record_by_image.dir/record_by_image.cpp.o
record_by_image: CMakeFiles/record_by_image.dir/build.make
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.9
record_by_image: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.9
record_by_image: CMakeFiles/record_by_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/zhenwei-qian/LinuxData/data/capture_window/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable record_by_image"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/record_by_image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/record_by_image.dir/build: record_by_image

.PHONY : CMakeFiles/record_by_image.dir/build

CMakeFiles/record_by_image.dir/requires: CMakeFiles/record_by_image.dir/record_by_image.cpp.o.requires

.PHONY : CMakeFiles/record_by_image.dir/requires

CMakeFiles/record_by_image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/record_by_image.dir/cmake_clean.cmake
.PHONY : CMakeFiles/record_by_image.dir/clean

CMakeFiles/record_by_image.dir/depend:
	cd /media/zhenwei-qian/LinuxData/data/capture_window/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/zhenwei-qian/LinuxData/data/capture_window /media/zhenwei-qian/LinuxData/data/capture_window /media/zhenwei-qian/LinuxData/data/capture_window/build /media/zhenwei-qian/LinuxData/data/capture_window/build /media/zhenwei-qian/LinuxData/data/capture_window/build/CMakeFiles/record_by_image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/record_by_image.dir/depend
