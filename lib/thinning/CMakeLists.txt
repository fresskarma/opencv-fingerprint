file(GLOB SourceFiles "*.h" "*.cpp")
add_library(
    ThinningAlgorithms
    GuoHall.cpp
    ZhangSuen.cpp
)
