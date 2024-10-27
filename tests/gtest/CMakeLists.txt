# Fetch the GoogleTest framework
CPMAddPackage(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2 
)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)

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

# Add a test for each test in the list
# Actually, we will add two tests for each test. One to build the test and one to run it.
foreach(test ${TestsToRun})
  
  get_filename_component(TName ${test} NAME_WE)

  add_executable(${TName} ${test})
  target_link_libraries(${TName} PRIVATE libLA GTest::GTest compiler_flags)

  gtest_discover_tests(${TName})

endforeach()
