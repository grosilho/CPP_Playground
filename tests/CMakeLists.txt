

# build the list of tests to run
# First we get all the .cpp files in the current directory and keep only the file name removing the full path
file(GLOB cpp_files_path "*.cpp")
set(cpp_files_names)
foreach(file_path ${cpp_files_path})
    get_filename_component(file_name ${file_path} NAME)
    list(APPEND cpp_files_names ${file_name})
endforeach()

# Every .cpp file must contain only one function with the same name as the file (without the extension), with signature int foo(int argc, char** argv)
set(TestsToRun ${cpp_files_names})

# Puts all the test functions in a single file RunTests.cpp. This decreases overall test size when using static libraries.
# Passing the name of a test function to the test executable RunTests will run that test only.
# Tests is a list of files needed to compile the RunTests executable.
create_test_sourcelist(Tests RunTests.cpp ${TestsToRun})

# add the executable compiling all tests
# the executable is not compiled by default but only if we ask for it.
# in this case it is compiled when the build_tests test is run.
add_executable(RunTests EXCLUDE_FROM_ALL)
target_sources(RunTests PRIVATE ${Tests})
target_link_libraries(RunTests PRIVATE libLA compiler_flags)

add_test(build_tests
  "${CMAKE_COMMAND}"
  --build "${CMAKE_BINARY_DIR}"
  --config "$<CONFIG>"
  --target RunTests
)
set_tests_properties(build_tests PROPERTIES FIXTURES_SETUP tests_fixtures) # this test will run before all the other tests, it sets up the test by compiling the RunTests executable

# Add a test for each test in the list
foreach(test ${TestsToRun})
  get_filename_component(TName ${test} NAME_WE)
  add_test(NAME ${TName} COMMAND RunTests ${TName}) # run RunTests with the test name as argument. This will runt that test only.
  set_tests_properties(${TName} PROPERTIES FIXTURES_REQUIRED tests_fixtures) # the test will run only after the tests_fixtures setup, which is build_tests
endforeach()
