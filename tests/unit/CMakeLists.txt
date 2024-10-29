# get the list of tests to run
file(
  GLOB cpp_files_names
  RELATIVE ${CMAKE_CURRENT_LIST_DIR}
  CONFIGURE_DEPENDS "*.cpp"
)

# Every .cpp file must contain only one function with the same name as the file (without the
# extension), with signature int foo(int argc, char** argv)
set(TestsToRun ${cpp_files_names})

# Put all the test functions in a single file RunTests.cpp. This decreases overall test size when
# using static libraries. Passing the name of a test function to the test executable RunTests will
# run that test only. Tests is a list of files needed to compile the RunTests executable.
create_test_sourcelist(Tests RunTests.cpp ${TestsToRun})

# add the executable compiling all tests
add_executable(RunTests)
target_sources(RunTests PRIVATE ${Tests})
target_link_libraries(RunTests PRIVATE LinAlg::LinAlg LinAlg::compiler_flags)

# Add a test for each test in the list
foreach(test ${TestsToRun})
  get_filename_component(TName ${test} NAME_WE)
  add_test(NAME ${TName} COMMAND RunTests ${TName}) # run RunTests with the test name as argument.
                                                    # This will runt that test only.
endforeach()
