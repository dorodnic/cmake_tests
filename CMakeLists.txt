cmake_minimum_required(VERSION 3.1.0)

project(user_app)

add_executable(user_app user_app.cpp)

target_compile_features(user_app PRIVATE cxx_std_11)

find_package(fractal REQUIRED)

target_link_libraries(user_app fractal)


