set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(GCC_COMPILER_VERSION "4.7" CACHE STRING "GCC Compiler version")

set(FLOAT_ABI_SUFFIX "")


set(CMAKE_C_COMPILER arm-linux-gnueabi${FLOAT_ABI_SUFFIX}-gcc-${GCC_COMPILER_VERSION})
set(CMAKE_CXX_COMPILER arm-linux-gnueabi${FLOAT_ABI_SUFFIX}-g++-${GCC_COMPILER_VERSION})
set(ARM_LINUX_SYSROOT /usr/arm-linux-gnueabi${FLOAT_ABI_SUFFIX} CACHE PATH "ARM cross compilation system root")


set(CMAKE_CXX_FLAGS "" CACHE STRING "c++ flags")
set(CMAKE_C_FLAGS "" CACHE STRING "c flags")
set(CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "shared linker flags")
set(CMAKE_MODULE_LINKER_FLAGS "" CACHE STRING "module linker flags")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-z,nocopyreloc" CACHE STRING "executable linker flags")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb -fdata-sections -Wa,--noexecstack -fsigned-char -Wno-psabi")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mthumb -fdata-sections -Wa,--noexecstack -fsigned-char -Wno-psabi")
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_MODULE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--fix-cortex-a8 -Wl,--no-undefined -Wl,--gc-sections -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now ${CMAKE_EXE_LINKER_FLAGS}")


set(CMAKE_FIND_ROOT_PATH "${CMAKE_FIND_ROOT_PATH} ${ARM_LINUX_SYSROOT}/lib")

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
 
message(STATUS "CMAKE_FIND_ROOT_PATH='${CMAKE_FIND_ROOT_PATH}'")

SET(CMAKE_INSTALL_RPATH "${ARM_LINUX_SYSROOT}/libhf")

