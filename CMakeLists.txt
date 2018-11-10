cmake_minimum_required(VERSION 3.1.0)

project(fractal)

set(CMAKE_CXX_STANDARD 11)

add_library(fractal src/fractal.cpp include/fractal/fractal.h)

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
