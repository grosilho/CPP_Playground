# execute only once
if(NOT PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  return()
endif()

# Helpful for debugging include(CMakePrintHelpers) cmake_print_variables(MY_VARIABLE)

# CPM Set the cache directory for CPM. First time you run look for a package it will download it in
# the cache. Next time you run cmake, it will use the version found in the cache.
set(CPM_SOURCE_CACHE
    "${CMAKE_CURRENT_LIST_DIR}/../external"
    CACHE STRING "The cache directory for CPM"
)
# Set to ON to first look for already installed package with find_package. If not found, then look
# in the cache directory. If not found, then download it.
option(CPM_USE_LOCAL_PACKAGES "Use local packages" ON)
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

# CCache
option(USE_CCACHE "Use ccache to speed up compilation" ON)
if(USE_CCACHE)
  set(CCACHE_OPTIONS "CCACHE_CPP2=true;CCACHE_SLOPPINESS=clang_index_store")
  CPMAddPackage(
    NAME Ccache.cmake
    GITHUB_REPOSITORY TheLartians/Ccache.cmake
    VERSION 1.2.5
  )
endif()

# Code formatting Check https://github.com/TheLartians/Format.cmake for usage Basically, it adds
# targets to format and check the code
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

# mdspan
CPMAddPackage(
  NAME mdspan
  GITHUB_REPOSITORY kokkos/mdspan
  GIT_TAG mdspan-0.6.0
)
