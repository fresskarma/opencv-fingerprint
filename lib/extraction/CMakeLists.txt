file(GLOB SourceFiles "*.h" "*.cpp")
add_library(
    ExtractionAlgorithms
    Filter.cpp
    Minutiae.cpp
    CrossingNumber.cpp
)
