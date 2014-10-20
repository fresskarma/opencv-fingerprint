cmake_minimum_required(VERSION 2.8.3)
project( OpenCVTest )
find_package( OpenCV REQUIRED )

#add_subdirectory(src)
#file(GLOB SourceFiles
#    "*.h"
#    "*.cpp"
#)

include_directories ("${PROJECT_SOURCE_DIR}/lib/thinning")
include_directories ("${PROJECT_SOURCE_DIR}/lib/binarisation")
include_directories ("${PROJECT_SOURCE_DIR}/lib/optimisation")

add_subdirectory(lib/thinning)
add_subdirectory(lib/binarisation)
add_subdirectory(lib/optimisation)

add_definitions( "-std=c++11" )

add_executable( ThinningTest src/ThinningTest.cpp )
add_executable( BinarisationTest src/BinarisationTest.cpp )

target_link_libraries( ThinningTest ${OpenCV_LIBS} ThinningAlgorithms )
target_link_libraries( BinarisationTest ${OpenCV_LIBS} ThinningAlgorithms BinarisationAlgorithms OptimisationAlgorithms )


