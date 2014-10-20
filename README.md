# Building

Requirements:

* CMake
* g++ or clang
* make
* OpenCV 2.4+

Change to the `build/` directory and run

    cmake ..
    make



# Cross compiling on Ubuntu 14.04

* Install cmake
* Install g++-4.7-arm-linux-gnueabihf
* Install gcc-4.7-arm-linux-gnueabihf


## Building opencv

Follow the instruction for building opencv [here](http://docs.opencv.org/doc/tutorials/introduction/crosscompilation/arm_crosscompile_with_cmake.html)

Notes:

* Replace compiler version 4.6 in `../platforms/linux/arm-gnueabi.toolchain.cmake` with 4.7 so that it bilds with the latest ubuntu stuff

I compiled OpenCV with

    cmake -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/arm-gnueabi.toolchain.cmake -DBUILD_opencv_superres=OFF -DCMAKE_INSTALL_PREFIX=/home/lucas/pj2/local/ ..



## Building  things

In build/ run:

    $ cmake -DCMAKE_TOOLCHAIN_FILE=../ArmToolchain.cmake -DOpenCV_DIR=/home/lucas/pj2/local/share/OpenCV  ..
    $ make
