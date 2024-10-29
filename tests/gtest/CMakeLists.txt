# Fetch the GoogleTest framework
CPMAddPackage(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)

# get the list of tests to run
file(
  GLOB cpp_files_names
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  CONFIGURE_DEPENDS "*.cpp"
)

set(TestsToRun ${cpp_files_names})

# Add a test for each test in the list Actually, we will add two tests for each test. One to build
# the test and one to run it.
foreach(test ${TestsToRun})

  get_filename_component(TName ${test} NAME_WE)

  add_executable(${TName} ${test})
  target_link_libraries(${TName} PRIVATE LinAlg::LinAlg LinAlg::compiler_flags GTest::GTest)

  gtest_discover_tests(${TName})

endforeach()
