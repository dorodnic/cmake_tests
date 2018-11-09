cmake_minimum_required(VERSION 3.1.0)

project(fractal)

set(CMAKE_CXX_STANDARD 11)

add_library(fractal src/fractal.cpp include/fractal/fractal.h)

target_include_directories(fractal PRIVATE include)
