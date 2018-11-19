cmake_minimum_required(VERSION 3.8.0)

project(fractal VERSION 1.0.0 LANGUAGES CXX)

add_library(fractal src/fractal.cpp include/fractal/fractal.h)

target_compile_features(fractal PRIVATE cxx_std_11)

target_include_directories(fractal PUBLIC 
    $<INSTALL_INTERFACE:include>    
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(fractal
    PROPERTIES
    PUBLIC_HEADER
    "include/fractal/fractal.h"
    )

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
    VERSION "${PROJECT_VERSION}" COMPATIBILITY AnyNewerVersion)

install(EXPORT fractalTargets FILE fractalTargets.cmake NAMESPACE fractal::
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fractalConfig.cmake"
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fractalConfigVersion.cmake"
    DESTINATION ${CMAKECONFIG_INSTALL_DIR})

option(BUILD_INSTALLER "Build Installer" ON)
if(BUILD_INSTALLER)
    add_subdirectory(installer)
endif()

option(BUILD_TOOLS "Build UI Tools" ON)
if(BUILD_TOOLS)
    add_subdirectory(tools)
endif()

