cmake_minimum_required(VERSION 3.8.0)

project(fractal-tests)

add_executable(unit-tests test.cpp)

target_include_directories(unit-tests PRIVATE ../include)
target_link_libraries(unit-tests fractal)

target_compile_features(unit-tests PRIVATE cxx_std_11)
