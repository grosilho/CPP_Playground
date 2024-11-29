# C++ Playground
This repository serves as a playground for experimenting with modern C++ features and continuous integration (CI) tools, with the added goal of testing and comparing their differences in practical applications.

To achieve this, I designed a small linear algebra library featuring multiple backends, each implemented using distinct approaches and showcasing different C++ capabilities. A key requirement for all backends is that they must evaluate all mathematical expressions lazily to maximize performance and flexibility.

Currently, the library includes two backends:

- Expression Templates (ET): An "old-school" implementation leveraging the well-established expression template technique.
- Ranges Library (RG): A modern implementation utilizing the C++ ranges library to express mathematical operations in a clean and declarative style.

Next Steps
- Implement a Third Backend: Explore the use of coroutines to build a new backend for lazy evaluation of mathematical expressions.
- Benchmarking Framework: benchmark and compare the performance of all backends.
The project aims to highlight the trade-offs and potential of different C++ paradigms while providing a lightweight framework for matrix operations.


## Main C++ features used in the backends
- ET: templates, expression templates, variadic templates, variable templates, fold expressions, template template classes, curiously recurring template pattern, 
- RG: std::ranges
- All: lambda functions, std::function, concepts, copy and swap idiom, move semantics


## CI tools currently employed
<!-- - CMake with CPM Package manager
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
- precompiled headers: for faster compilation -->

CMake, CPM Package Manager, Ccache, Git, Github actions, Docker, Caching Docker image, lcov, codecov, CDash, doctest, Doxyge, clang-format, cmake-format, precompiled headers.
