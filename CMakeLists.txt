# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define CMake options ---------------------------------------------------------
option(BUILD_TESTING "Configure tests" OFF)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "The installation directory")
# set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "The build type")
set(ENV{CMAKE_GENERATOR} "Ninja")

# Define the compiler flags ----------------------------------------------------
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)
target_compile_options(compiler_flags INTERFACE "-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused")

# Import dependencies -----------------------------------------------------------
include(cmake/import_dependencies.cmake)

# Define the project -----------------------------------------------------------
project(LinAlg 
        VERSION 1.0 
        LANGUAGES CXX
        DESCRIPTION "A simple project to practice C++, CMake.")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
        message(FATAL_ERROR "In-source builds not allowed. Please use a build directory and run CMake from there.")
endif()

# Add subdirectories
add_subdirectory(include/${PROJECT_NAME})

# Configure tests. If the project is the main project and BUILD_TESTING is ON, then enable testing.
# Hence tests are not configures if we are building the library as part of another project.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
   enable_testing()
   add_subdirectory(tests)
endif()

# Install, export and packing -----------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/cmake/run_install.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/run_export.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/run_packing.cmake)
