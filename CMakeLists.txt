# Minimum version 3.28, for C++20 modules support
cmake_minimum_required(VERSION 3.28)

# Define the options -----------------------------------------------------------
option(BUILD_TESTING "Configure tests" ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "The installation directory")
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "The build type")

# Define the project -----------------------------------------------------------
project(libLA 
        VERSION 1.0 
        LANGUAGES CXX
        DESCRIPTION "A simple project to practice C++, CMake.")

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
        message(FATAL_ERROR "In-source builds not allowed. Please use a build directory and run CMake from there.")
endif()

# Add dependencies -----------------------------------------------------------
# CPM (package manager for cmake)
set(CPM_SOURCE_CACHE ${CMAKE_SOURCE_DIR}/external)
option(CPM_USE_LOCAL_PACKAGES "Use local packages" ON)
include(cmake/CPM.cmake)

# CCache
option(USE_CCACHE "Use ccache to speed up compilation" ON)
set(CCACHE_OPTIONS "CCACHE_CPP2=true;CCACHE_SLOPPINESS=clang_index_store")
CPMAddPackage(
  NAME Ccache.cmake
  GITHUB_REPOSITORY TheLartians/Ccache.cmake
  VERSION 1.2.5
)

# Define the compiler flags ----------------------------------------------------
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)
target_compile_options(compiler_flags INTERFACE "-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused")

# Add subdirectories
add_subdirectory(${PROJECT_NAME})

# Main executable (optional)
add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE ${PROJECT_NAME} compiler_flags)

# Configure tests. If the project is the main project and BUILD_TESTING is ON, then enable testing.
# Hence tests are not configures if we are building the library as part of another project.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
   enable_testing()
   add_subdirectory(tests)
endif()

# --------------------------------------------------------------------------------------------
# Install, export and packing
include(${CMAKE_SOURCE_DIR}/cmake/run_install.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/run_export.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/run_packing.cmake)
