cmake_minimum_required(VERSION 3.1.0)

project(fractal)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_COVERAGE "Build with Code-Coverage" OFF)
if(BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") # debug, no optimisation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # enabling coverage
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
endif()

find_package(OpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(fractal src/fractal.cpp src/fractal.def include/fractal/fractal.h)

add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(fractal -fprofile-arcs)

target_include_directories(fractal PRIVATE include)

set_target_properties(fractal
    PROPERTIES
    PUBLIC_HEADER
    "include/fractal/fractal.h"
    )

set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

install(TARGETS fractal
    EXPORT fractalTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fractal"
)

set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/fractal DESTINATION include)

set(CMAKECONFIG_INSTALL_DIR lib/cmake/fractal)

include(CMakePackageConfigHelpers)
configure_package_config_file(fractalConfig.cmake.in fractalConfig.cmake
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/bin
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/fractalConfigVersion.cmake"
    VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}" COMPATIBILITY AnyNewerVersion)

install(EXPORT fractalTargets FILE fractalTargets.cmake NAMESPACE fractal::
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fractalConfig.cmake"
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fractalConfigVersion.cmake"
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})

option(BUILD_UNIT_TESTS "Build Unit-Tests" ON)
if(BUILD_UNIT_TESTS)
    add_subdirectory(test)
endif()

option(BUILD_INSTALLER "Build Installer" ON)
if(BUILD_INSTALLER)
    add_subdirectory(installer)
endif()

option(BUILD_TOOLS "Build UI Tools" ON)
if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()
