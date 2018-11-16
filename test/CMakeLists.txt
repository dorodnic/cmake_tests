cmake_minimum_required(VERSION 3.1.0)

project(fractal-tests)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

add_executable(unit-tests test.cpp)

target_include_directories(unit-tests PRIVATE ../include)
target_link_libraries(unit-tests fractal)
