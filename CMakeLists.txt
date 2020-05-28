cmake_minimum_required (VERSION 3.8)


project (ray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fopenmp")

add_executable (ray  main.cpp Figure.h Figure.cpp Factory.h FactoryBox.h FactoryTetra.h FactorySphere.h CImg.h functions.h functions.cpp RGB.h Ray.h Ray.cpp Point.h Box.h Box.cpp Tetra.h Tetra.cpp Sphere.h Sphere.cpp)