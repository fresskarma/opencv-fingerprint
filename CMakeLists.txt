cmake_minimum_required(VERSION 2.8.3)
project( OpenCVTest )
find_package( OpenCV REQUIRED )

#add_subdirectory(src)
#file(GLOB SourceFiles
#    "*.h"
#    "*.cpp"
#)

include_directories ("${PROJECT_SOURCE_DIR}/lib/thinning")
add_subdirectory(lib/thinning)
add_executable( ThinningTest src/ThinningTest.cpp )

target_link_libraries( ThinningTest ${OpenCV_LIBS} ThinningAlgorithms )


