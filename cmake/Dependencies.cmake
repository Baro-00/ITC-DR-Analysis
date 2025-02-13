include(FetchContent)

function(fetch_dependencies)
    # Eigen package
    # First, check if there is a local installation
    if(EXISTS "${PROJECT_SOURCE_DIR}/include/external/eigen/Eigen/Core")
        message(STATUS "Using local Eigen installation")
        add_library(Eigen3::Eigen INTERFACE IMPORTED)
        set_target_properties(Eigen3::Eigen PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include/external/eigen"
        )
    else()
        # If not, download it
        find_package(Eigen3 3.3 QUIET)
        if(NOT Eigen3_FOUND)
            message(STATUS "Eigen not found. Downloading...")
            FetchContent_Declare(
                eigen
                GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
                GIT_TAG 3.4.0
            )
            FetchContent_MakeAvailable(eigen)
        endif()
    endif()

    # GoogleTest package
    find_package(GTest QUIET)
    if(NOT GTest_FOUND)
        message(STATUS "GoogleTest not found. Downloading...")
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
        )
        # Disable installation of GoogleTest
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    # Doxygen package
    find_package(Doxygen QUIET)
    if(NOT DOXYGEN_FOUND AND BUILD_DOCS)
        message(WARNING "Doxygen not found. Documentation will not be generated.")
        set(BUILD_DOCS OFF CACHE BOOL "Build documentation" FORCE)
    endif()
endfunction()