# when adding the examples and test folder to the project use EXCLUDE_FROM_ALL

# Useful variables:
# CMAKE_CURRENT_SOURCE_DIR
# CMAKE_CURRENT_BINARY_DIR
# CMAKE_SOURCE_DIR
# CMAKE_BINARY_DIR
# PROJECT_SOURCE_DIR
# CMAKE_INSTALL_PREFIX

# Useful commands:
# project: the project name. Eventually, version, language, description can be added.
# add_subdirectory: add a subdirectory to the build. It should contain a CMakeLists.txt. Cmake will process it and then continue processing the current file. Like calling a funciton in a script.
# add_executable: add an executable to the build. Source files can be added now or later using target_sources.
# add_library: add a library to the build. Source file can be added now or later using target_sources.
# target_sources: add source files to a target.
# target_include_directories: add the directories containing the header files needed by the target.
# target_link_libraries: add the libraries needed by the target. Can be libraries that we defined with add_library or external ones. This is used by the linker.
# target_compile_features: specify the features required by the target. Like constexpr, auto, etc. We can as well specify the standard required by the target. For a list see: https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html
# target_compile_definitions: add compiler definitions to the target. Like -D in the compiler command line.
# target_compile_options: add compiler options to the target. Like -O2, -Wall, etc. These are not used by the linker!
# target_link_options: add linker options to the target. Like -L, -l, etc. 
# target_link_directories: add directories to the linker search path. This is not recommended. Use target_link_libraries instead.
# include_directories: add the directories to all targets of the current CMakelists.txt. This is not recommended. Use target_include_directories instead.
# option: add a variable and set it to a defualt value. Can be used to enable or disable some features. We can change it at configuration time using -D followed by the option name and the =ON or =OFF
# install: install the given target or targets. We can give an executable, a library, files. Usually texecutable go to bin, libraries to lib, and .h files to include. The given destination directoreis are relative to the CMAKE_INSTALL_PREFIX.
# enable_testing: enable testing for the project. Called after the library is built (i.e. at the end of the CMakeLists.txt). 

# Often the target_* commands ask for the PUBLIC, PRIVATE or INTERFACE keyword. Their meaning is:
# PUBLIC: the property is applied to the target and to all targets that use (link to) it.
# PRIVATE: the property is applied to the target only.
# INTERFACE: the property is applied to all targets that use the (link to) target.

# Hints
# - Sometimes to compile a .cxx file do not need to add the path to the corresponding .h file. This is because the compiler will look for the .h file in the same directory as the .cxx file.
#   However, the files using the resulting library do need the .h file, which is likely to be in a different directory. Hence, we need to use target_include_directories to add such directory.
#   And we need to do so for all files using the library. A better way is to add the directory already to the library target with the INTERFACE keyword. 
#   This way, all targets using the library will have the directory added automatically.
# - if we define a library in a file, we can use it in the smae file and also in subforder files, as long the library is defined before the call to add_subdirectory.
# - it is common to define interface libraries, which are fictitious libraries that are not compiled. They are used to group together some include directories, compile features, etc.
#   For instance we can define an interface library and set the compilation options, then link this library to all other libraries and executables. This way, all targets will have the same options.

# Steps to write a CmakeLists.txt:
# - Set cmake minimum version.
# - Define the project with the project command.
# - Define some variables if needed. Like C++ standard, compiler flags, etc.
# - If needed, add the subdirectories to the project using add_subdirectory.
# - Add libraries and executables to the project using add_library and add_executable.
# - For each one think about the include directories, source files, link libraries.
# - Once the library is build, enable testing.

cmake_minimum_required(VERSION 3.28)

project(PracticeCPP 
        VERSION 1.0 
        LANGUAGES CXX
        DESCRIPTION "A simple project to practice C++, CMake.")

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)
target_compile_options(compiler_flags INTERFACE "-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused")

add_subdirectory(libLA)

add_executable(main)
target_sources(main PRIVATE main.cpp)
target_link_libraries(main PRIVATE libLA compiler_flags)
