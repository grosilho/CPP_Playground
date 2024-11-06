# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the project
# ---------------------------------------------------------------------------------------
project(
  LinAlg
  VERSION 1.0
  LANGUAGES CXX
  DESCRIPTION "A simple project to practice C++, CMake."
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please use a build directory and run CMake from there."
      )
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Define the compiler flags
# ---------------------------------------------------------------------------------------
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)
target_compile_options(compiler_flags INTERFACE "-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused")

# Import dependencies
# ---------------------------------------------------------------------------------------
include(cmake/import_dependencies.cmake)

add_subdirectory(include/LinAlg)
