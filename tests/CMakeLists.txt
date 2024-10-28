# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the project -----------------------------------------------------------
project(Tests 
        VERSION 1.0 
        LANGUAGES CXX
        DESCRIPTION "A simple project to practice C++, CMake.")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
        message(FATAL_ERROR "In-source builds not allowed. Please use a build directory and run CMake from there.")
endif()

# Import dependencies -----------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)
CPMAddPackage(NAME LinAlg SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

enable_testing()

# Add subdirectories
add_subdirectory(unit)
add_subdirectory(gtest)
