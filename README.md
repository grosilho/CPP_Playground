# C++ Playground
A repository where I exercise with Modern C++ and use common CI tools. A linear algebra library is used as dummy application.

## CI tools currently employed
- CMake with CPM Package manager
- Ccache: to cache compiled objects and speedup compilation, used both locally and in Github actions
- Git
- Github actions: for building, testing and running code coverage at each commit
- Docker: used as virtual machine in the Github actions workflow
- Caching the Docker image to avoid rebuilding it at each commit
- lcov: for generating code coverage reports
- codecov: dashboard to show code coverage results
- CDash: dashboard for showing tests results
- doctest: for the unit tests framework
- Doxygen: for code documentation
- clang-format: for nice and automatic C++ code formatting
- cmake-format: similar for CMakeLists files
- precompiled headers: for faster compilation

## C++ language features and techniques employed
- templates
- expression templates
- variadic templates
- variable templates
- fold expressions
- template template classes
- curiously recurring template pattern
- copy and swap idiom
- move semantics
- lambda functions
- std::span
- std::mdspan
- std::ranges
- std::function
- std::conditional
- std::initializer_list


### Previously implmented but removed
- Modules: removed due to poor support
