cmake_minimum_required(VERSION 3.8.0)

project(fractal-tools)

set(FRACTAL_UI_INCLUDES ../include)
set(FRACTAL_UI_DEPENDENCIES fractal glfw3)

find_package(OpenGL)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL package not found!")
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

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    LIST(APPEND FRACTAL_UI_DEPENDENCIES ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
elseif(UNIX)
    find_package(Threads REQUIRED)
    find_library(x11 NAMES X11)
    find_library(xrandr NAMES Xrandr)
    find_library(xcursor NAMES Xcursor)
    find_library(xi NAMES Xi)
    find_library(xxf86vm NAMES Xxf86vm)
    find_library(dl NAMES dl)
    find_library(xinerama NAMES Xinerama)
    list(APPEND FRACTAL_UI_DEPENDENCIES Threads::Threads ${x11} ${xrandr} ${xi} ${xxf86vm} ${dl} ${xcursor} ${xinerama})
endif()

add_executable(fractal-ui fractal-ui.cpp)

target_compile_features(fractal-ui PRIVATE cxx_std_11)

target_include_directories(fractal-ui PRIVATE ${FRACTAL_UI_INCLUDES})
target_link_libraries(fractal-ui ${FRACTAL_UI_DEPENDENCIES})

add_dependencies(fractal-ui external_glfw)

install(
    TARGETS fractal-ui
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
