cmake_minimum_required(VERSION 3.8.0)

project(fractal VERSION 1.0.0 LANGUAGES CXX)

add_library(fractal src/fractal.cpp include/fractal/fractal.h)

target_compile_features(fractal PRIVATE cxx_std_11)

target_include_directories(fractal PUBLIC include)
