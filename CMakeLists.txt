# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.29)

# Define the project
# ---------------------------------------------------------------------------------------
project(
  LinAlg
  VERSION 1.0
  LANGUAGES CXX
  DESCRIPTION "A simple project to practice C++, CMake."
)

# We are not using modules anymore
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

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
set(RELEASE_COMPILE_OPTIONS "-O3;-fdiagnostics-color=always")
set(DEBUG_COMPILE_OPTIONS "-Og;-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused;-fdiagnostics-color=always")
target_compile_options(compiler_flags INTERFACE "$<$<CONFIG:Release,MinSizeRel>:${RELEASE_COMPILE_OPTIONS}>" "$<$<CONFIG:Debug>:${DEBUG_COMPILE_OPTIONS}>")
#"-pedantic-errors;-Weffc++;-Wconversion;-Wsign-conversion;-Werror"
                

# Import dependencies
# ---------------------------------------------------------------------------------------
include(cmake/import_dependencies.cmake)

add_subdirectory(include/LinAlg)
