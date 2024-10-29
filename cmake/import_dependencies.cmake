# execute only once
if(NOT PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  return()
endif()

# CPM
set(ENV{CPM_SOURCE_CACHE} ${CMAKE_CURRENT_LIST_DIR}/../external)
option(CPM_USE_LOCAL_PACKAGES "Use local packages" ON)
include(${CMAKE_CURRENT_LIST_DIR}/CPM.cmake)

# CCache
option(USE_CCACHE "Use ccache to speed up compilation" ON)
set(CCACHE_OPTIONS "CCACHE_CPP2=true;CCACHE_SLOPPINESS=clang_index_store")
CPMAddPackage(
  NAME Ccache.cmake
  GITHUB_REPOSITORY TheLartians/Ccache.cmake
  VERSION 1.2.5
)

CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")
