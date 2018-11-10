cmake_minimum_required(VERSION 3.1.0)

project(fractal-tools)

set(CMAKE_CXX_STANDARD 11)

set(FRACTAL_UI_INCLUDES ../include)
set(FRACTAL_UI_DEPENDENCIES fractal glfw3)

find_package(OpenGL)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "\n\n OpenGL package is missing!\n\n")
endif()
list(APPEND FRACTAL_UI_DEPENDENCIES ${OPENGL_LIBRARIES})

include(ExternalProject)

ExternalProject_Add(
	external_glfw

    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.2"

    UPDATE_COMMAND ""
    PATCH_COMMAND ""

    SOURCE_DIR "third-party/glfw/"
    CMAKE_ARGS -DCMAKE_CXX_STANDARD_LIBRARIES=${CMAKE_CXX_STANDARD_LIBRARIES}
               -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
               -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/glfw_install
               -DBUILD_SHARED_LIBS=false
    TEST_COMMAND ""
)
        
list(APPEND FRACTAL_UI_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/glfw_install/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/glfw_install/lib)

add_executable(fractal-ui fractal-ui.cpp)

target_include_directories(fractal-ui PRIVATE ${FRACTAL_UI_INCLUDES})
target_link_libraries(fractal-ui ${FRACTAL_UI_DEPENDENCIES})

add_dependencies(fractal-ui external_glfw)

install(
    TARGETS fractal-ui
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
