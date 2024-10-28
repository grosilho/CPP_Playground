# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the project -----------------------------------------------------------
project(standalone 
        VERSION 1.0 
        LANGUAGES CXX
        DESCRIPTION "A simple project to practice C++, CMake.")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
        message(FATAL_ERROR "In-source builds not allowed. Please use a build directory and run CMake from there.")
endif()

# Import dependencies -----------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)
CPMAddPackage(NAME LinAlg SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# Add subdirectories
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE LinAlg compiler_flags)
