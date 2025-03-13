cmake_minimum_required(VERSION 3.15)

# Project
project(ITCDeadReckoningAnalysis 
    VERSION 1.0.0 
    DESCRIPTION "System nawigacji inercyjnej z fuzją sensorów"
    LANGUAGES CXX
)

# Cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include dependencies
include(Dependencies)
fetch_dependencies()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options

option(BUILD_TESTS "Build the test suite" ON)
# TODO: Fix documentation (and uncomment the line below)
# option(BUILD_DOCS "Build documentation" OFF)
option(ENABLE_WARNINGS "Enable all warnings" ON)

# Warnings
if(ENABLE_WARNINGS)
    if(MSVC)
        add_compile_options(/W4 /WX)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

# Add subdirectories
add_subdirectory(src)

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Documentation
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    endif()
endif()

# # TODO: What is this?
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#     "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
#     VERSION ${PROJECT_VERSION}
#     COMPATIBILITY SameMajorVersion
# )

# # Install config
# install(TARGETS nav_components
#     EXPORT ${PROJECT_NAME}Targets
#     LIBRARY DESTINATION lib
#     ARCHIVE DESTINATION lib
#     RUNTIME DESTINATION bin
#     INCLUDES DESTINATION include
# )

# # Install headers
# install(DIRECTORY src/
#     DESTINATION include
#     FILES_MATCHING PATTERN "*.h"
# )

# # Install config files
# install(EXPORT ${PROJECT_NAME}Targets
#     FILE ${PROJECT_NAME}Targets.cmake
#     NAMESPACE ${PROJECT_NAME}::
#     DESTINATION lib/cmake/${PROJECT_NAME}
# )