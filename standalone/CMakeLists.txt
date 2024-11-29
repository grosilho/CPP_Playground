cmake_minimum_required(VERSION 3.28)

# Define the project -----------------------------------------------------------
project(
  standalone
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

# We are not using modules anymore
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Import dependencies
# -----------------------------------------------------------
include(${CMAKE_CURRENT_LIST_DIR}/../cmake/import_dependencies.cmake)

# Add executable
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

set(LOADING_METHOD
    "1"
    CACHE STRING "Method to load LinAlg project"
)

# Here we list different options to load the LinAlg project. Option 1 and 2: First try to find an
# installed version of LinAlg. If it doesnt, build LinAlg as part of the current project. Options
# 3,4 work only if the LinAlg project is alread installed in ../install_${CMAKE_BUILD_TYPE}
if(LOADING_METHOD STREQUAL "1")
  # Option 1: Here it will not find any installed version of LinAlg because we are not giving the
  # source directory. Hence it will include the LinAlg project and build it.
  CPMAddPackage(NAME LinAlg SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
elseif(LOADING_METHOD STREQUAL "2")
  # Option 2: Here we give the source directory, so it will find the configuration file and there is
  # no need to build LinAlg as part of the current project.
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../install_${CMAKE_BUILD_TYPE}")
  CPMAddPackage(NAME LinAlg SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/..")
elseif(LOADING_METHOD STREQUAL "3")
  # Option 3: Manually find the installed version of LinAlg and load the cmake file
  include(
    "${CMAKE_CURRENT_LIST_DIR}/../install_${CMAKE_BUILD_TYPE}/lib/cmake/LinAlg/LinAlgTargets.cmake"
  )
elseif(LOADING_METHOD STREQUAL "4")
  # Option 4: Look for the config file in the install directory
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../install_${CMAKE_BUILD_TYPE}")
  find_package(LinAlg REQUIRED)
endif()

# Note that in Option 1 CPMAddPackage loads the targets without prepending any namespace. Indeed, it
# reads their definition as it is in the CMakeLists file and not as it is exported in the .cmake
# file. Therefore, in LinAlg project we define aliases of the targets, where we prepend the
# namespace. In that way, in the current project we can use the targets with namespace. Hence, we
# have a uniform sintax as if they were loaded with find_package.

target_link_libraries(${PROJECT_NAME} PRIVATE LinAlg::LinAlg LinAlg::compiler_flags)
