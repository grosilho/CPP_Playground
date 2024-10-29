# Instructions: 1) conf, build, run tests 2) generate coverage report 3) generate html version cmake
# --workflow --preset debug lcov -c -d ../build/tests_Debug -o
# ../build/tests_Debug/main_coverage.info genhtml ../build/tests_Debug/main_coverage.info
# --output-directory ../coverage_html

# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the project
# --------------------------------------------------------------------
project(Tests)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please use a build directory and run CMake from there."
  )
endif()

# Options
# -------------------------------------------------------------------------------
option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)
option(TEST_COVERAGE_ONLY_LIBRARY "Only test the library" ON)

# Import dependencies
# -------------------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)
if(ENABLE_TEST_COVERAGE)
  include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CodeCoverage.cmake)
endif()

# Add library
# ---------------------------------------------------------------------------
CPMAddPackage(NAME LinAlg SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
if(ENABLE_TEST_COVERAGE AND TEST_COVERAGE_ONLY_LIBRARY)
  append_coverage_compiler_flags_to_target(LinAlg)
elseif(ENABLE_TEST_COVERAGE) # test everything that is compiled
  append_coverage_compiler_flags()
endif()

enable_testing()

# Add subdirectories
add_subdirectory(unit)
add_subdirectory(gtest)
add_subdirectory(doctest)
