# Fetch the doctest framework
CPMAddPackage("gh:doctest/doctest@2.4.9")

# get the sources
file(
  GLOB_RECURSE sources
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  CONFIGURE_DEPENDS "*.cpp"
)
add_executable(tests_doctest ${sources})
target_link_libraries(tests_doctest doctest::doctest LinAlg::LinAlg)
target_include_directories(tests_doctest PUBLIC ${CMAKE_CURRENT_LIST_DIR})

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(tests_doctest)
