# PracticingModernCpp_app_LinearAlgebra
A repository where I exercise with Modern C++ and use common CI tools.

## CI tools currently employed
- CMake with CPM Package manager
- Ccache: to cache compiled objects and speedup compilation. Used both locally and in Github actions.
- Git
- Github actions: for building, testing and running code coverage at each commit
- Docker: used as virtual machine in the Github actions workflow
- Caching the Docker image to avoid rebuilding at each commit
- lcov: for generating code coverage reports
- codecov: dashboard to show code coverage results
- CDash: dashboard for showing tests results
- doctest: for the unit tests framework
- Doxygen: for code documentation
- clang-format: for nice and automatic C++ code formatting
- cmake-format: similar for CMakeLists files

## C++ language features employed
- Templates
- Modules
- mdspan
- copy and swap idiom
