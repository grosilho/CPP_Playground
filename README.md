
# C++ linear algebra playground

This repository implements a small linear algebra library in C++ with two distinct backends for performing operations on matrices and vectors. Both backends are designed to evaluate operations lazily, offering efficiency and flexibility.


## Goals of the Project

### 1. Refreshing C++ Skills
After spending a period working with Python, I wanted to refresh my C++ skills, focusing on modern and advanced techniques. This project utilizes features such as: ranges and views, concepts, expression templates, variadic templates and fold expressions, universal references, template template classes, among others.

### 2. Exploring Modern C++ Development Tools
The project also allowed me to refine my understanding and usage of modern development tools for C++: CMake, code coderage with lcov, unit testing with doctest, Ccache, github actions and containerization with Docker, precompiled headers.

### 3. Comparing Backends for Lazy Evaluation
The project sought to compare the efficiency of two backends designed for lazy evaluation of linear algebra operations:

- The **established expression templates approach**.
- The **modern ranges/views-based approach**.

### 4. Investigating Custom (CST) Containers vs STL Containers
Another key motivation was to explore whether a very simple user-implemented container could achieve the same level of efficiency as `std::vector`, the standard container for dynamic arrays in C++.


## Overview of the Backends

1. **Expression Templates Backend (ET)**:
Implements linear algebra operations using the classic expression template approach.

2. **Ranges and Views Backend (RG)**:
Leverages the modern C++ Ranges and Views library for lazy evaluation of operations.
   
In both backends the underlying container for storing matrix and vector coefficients is templetized. By default, ET uses `std::vector` and RG uses a custom container implemented from scratch. 

## Performance Comparison
This section presents the results of performance comparisons between the two backends. The analysis is divided into two parts.

In the following plots we denote: $A,B,C,D$ square matrices of size $N$; $s,r$ real numbers; $f(x)=x^2+1$ a function applied element-wise to the matrices coefficients. Operators $+,-,*,/$ are applied element-wise, while @ represents the matrix-matrix multiplication.

### 1. **Comparison of Underlying Containers: STL VS CST**
Here, we evaluate the performance difference between `std::vector` (STL) and the custom-made (CST) container. To do so, we first consider matrices using the RG backend and `std::vector` as underlying container, and perform some simple memory acces and/or write operations on the coefficients. We consider different matrix sizes ($N$) and measure CPU time. We denote these experiments STL. Then we perform the same experiments using again matrices with the RG backend but now using the custom-made container for storing the coefficients. We denote these experiments CST.

<table align="center" style="border-collapse: collapse; border: none">
  <tr>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/copy_matrix.png"/><br>
    <em>Matrix deep copy: A=B.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/set_operator.png"/><br>
    <em>Set operator: A[i,j] for all i,j.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/apply_inplace_fun.png"/><br>
    <em>Apply f(x) element-wise: f(A).</em>
    </td>
  </tr>
</table>
<table align="center" style="border-collapse: collapse; border: none">
  <tr>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/LU_factorization.png"/><br>
    <em>LU factorization of A.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/mult_four_mat.png"/><br>
    <em>Matrices multiplication: A@B@C@D.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/long_op_1.png"/><br>
    <em>Perform element-wise:<br>E = A * (s + B) + (C - r * A) / f(D).</em>
    </td>
  </tr>
</table>


### 2. **Comparison of Backend Approaches: ET VS RG**
In this subsection, we focus on the difference in performance between the classic expression templates (ET) approach and the modern ranges/views (RG) approach. We perform some linear algebra expressions on matrices using the ET and RG backends and compare the CPU times. In both cases, the underlying container is `std::vector`.


<table align="center" style="border-collapse: collapse; border: none">
  <tr>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/mult_elwise_two_mat.png"/><br>
    <em>Element-wise multiplication: A*B.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/mult_with_scalar.png"/><br>
    <em>Sum with scalar: A+s.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/mult_two_expr.png"/><br>
    <em>Matrix multiplication of two expressions:<br>(A * B + C * D) @ (B * C - D * A).</em>
    </td>
  </tr>
</table>
<table align="center" style="border-collapse: collapse; border: none">
  <tr>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/sum_four_mat.png"/><br>
    <em>Sum of four matrices: A+B+C+D.</em>
    </td>
    <td valign="top", style="text-align: center; border: none;">
    <img height=170 src="./benchmarks/results/long_op_2.png"/><br>
    <em>Perform element-wise:<br>E = A * (s + B) + (C - r * A) / f(D).</em>
    </td>
  </tr>
</table>



## Conclusion
From the plots, we observe the following:

1. At least for the very simple test cases evaluated here, the custom-made container is as efficient as the STL `std::vector` container. I do not claim that the custom container will always be as efficient. More extensive experiments, particularly those involving a variety of algorithms from the STL, would likely reveal that the custom-made container is slower in many situations. Nevertheless, for the specific use case tested, the custom implementation performs on par with the STL container.

2. The two approaches, using expression templates (ET) and ranges/views (RG), exhibit very similar performance. This suggests that the modern ranges/views approach can be a viable alternative to expression templates for lazy evaluation of linear algebra operations, without incurring significant performance penalties.

Of course, this is a small linear algebra library with limited functionalities and we performed tests on dense squared matrices of size $N$ at most 8192. Extending the library and the benchmarks may change the results.


#
### Running the Code

**Running tests:**
Test are run by executing:
```
cd tests && cmake --workflow --preset Debug
```
This will compile the library and run the tests.

**Running benchmarks:**
Benchmarks are run by executing:
```
cd benchmarks && ./scripts/benchmark.sh
```
This will compile the library, run the benchmarks and generate plots in `benchmarks/results`.


**Use in another project:**
Run
```
cmake -S . -B build && cmake --install build --prefix install_dir
```
Then use it in your CMake file 
```
list(APPEND CMAKE_PREFIX_PATH "path/to/install_dir")
find_package(LinAlg REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE LinAlg::LinAlg LinAlg::compiler_flags)
```
