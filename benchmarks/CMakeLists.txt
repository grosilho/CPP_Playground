
cmake_minimum_required(VERSION 3.28)

# Define the project
# --------------------------------------------------------------------
project(Benchmarks)

# We are not using modules anymore
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please use a build directory and run CMake from there."
  )
endif()

# Options
# -------------------------------------------------------------------------------
OPTION(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(CMAKE_BUILD_TYPE Release)

# Import dependencies
# -------------------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)
CPMAddPackage("gh:google/benchmark@1.9.1")
CPMAddPackage(NAME LinAlg SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# get the sources
file(
  GLOB_RECURSE sources
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  CONFIGURE_DEPENDS "*.cpp"
)
add_executable(benchmarks ${sources})
target_link_libraries(benchmarks benchmark::benchmark LinAlg::LinAlg)
target_link_libraries(benchmarks profiler)
target_include_directories(benchmarks PUBLIC ${CMAKE_CURRENT_LIST_DIR})
