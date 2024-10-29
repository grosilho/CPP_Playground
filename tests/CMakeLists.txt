# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the project --------------------------------------------------------------------
project(Tests)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
        message(FATAL_ERROR "In-source builds not allowed. Please use a build directory and run CMake from there.")
endif()

# Options -------------------------------------------------------------------------------
option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# Import dependencies -------------------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

# Add library ---------------------------------------------------------------------------
if(TEST_INSTALLED_VERSION)
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/../install_${CMAKE_BUILD_TYPE})
    find_package(LinAlg REQUIRED)
    if(ENABLE_TEST_COVERAGE)
        target_compile_options(LinAlg::compiler_flags INTERFACE -O0 -g -fprofile-arcs -ftest-coverage)
        target_link_options(LinAlg::compiler_flags INTERFACE -fprofile-arcs -ftest-coverage)
    endif()
else()
    CPMAddPackage(NAME LinAlg SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
    if(ENABLE_TEST_COVERAGE)
        target_compile_options(compiler_flags INTERFACE -O0 -g -fprofile-arcs -ftest-coverage)
        target_link_options(compiler_flags INTERFACE -fprofile-arcs -ftest-coverage)
    endif()
endif()


enable_testing()

# Add subdirectories
add_subdirectory(unit)
add_subdirectory(gtest)
add_subdirectory(doctest)
