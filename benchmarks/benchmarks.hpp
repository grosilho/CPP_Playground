#include "../include/Solvers/Solvers.hpp"
#include "../tests/doctest/backends.hpp"

#include <benchmark/benchmark.h>

// Allocate ---------------------------------------------------------------------
template <typename Matrix>
static void allocate_matrix(benchmark::State& state)
{
    for (auto _ : state)
        benchmark::DoNotOptimize(Matrix(state.range(0), state.range(0)));
    state.SetComplexityN(state.range(0));
}

// Set operator -----------------------------------------------------------------
template <typename Matrix>
static void set_operator(benchmark::State& state)
{
    Matrix m(state.range(0), state.range(0));

    for (auto _ : state)
    {
        // benchmark::DoNotOptimize(m.data().data());
        for (int i = 0; i < m.rows(); ++i)
            for (int j = 0; j < m.cols(); ++j)
                benchmark::DoNotOptimize(m[i, j] = i * m.cols() + j);
        // benchmark::ClobberMemory();
    }
    state.SetComplexityN(state.range(0));
}

// Copy operator -----------------------------------------------------------------
template <typename Matrix>
static void copy_operator(benchmark::State& state)
{
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));

    for (auto _ : state)
    {
        Matrix m2(m1);
    }
    state.SetComplexityN(state.range(0));
}

// Move operator -----------------------------------------------------------------
template <typename Matrix>
static void move_operator(benchmark::State& state)
{
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m2 = std::move(m1));
        benchmark::DoNotOptimize(m1 = std::move(m2));
    }
    state.SetComplexityN(state.range(0));
}

// apply operator -----------------------------------------------------------------
template <typename Matrix>
static void apply_operator(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Scalar (&std_fun)(Scalar) = std::cos;

    for (auto _ : state)
    {
        Matrix m2;
        benchmark::DoNotOptimize(m2 = m1.apply(std_fun));
    }
    state.SetComplexityN(state.range(0));
}

// apply_inplace operator -----------------------------------------------------------------
template <typename Matrix>
static void apply_inplace_operator(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Scalar (&std_fun)(Scalar) = std::cos;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m1.apply_inplace(std_fun));
    }
    state.SetComplexityN(state.range(0));
}

// Sum two matrices -----------------------------------------------------------------
template <typename Matrix>
static void sum_two(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m3 = m1 + m2);
    }
    state.SetComplexityN(state.range(0));
}

// Sum four matrices -----------------------------------------------------------------
template <typename Matrix>
static void sum_four(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3 = Matrix::randn(state.range(0), state.range(0));
    Matrix m4 = Matrix::randn(state.range(0), state.range(0));
    Matrix m5;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m5 = m1 + m2 + m3 + m4);
    }
    state.SetComplexityN(state.range(0));
}

// Sum with scalar -----------------------------------------------------------------
template <typename Matrix>
static void sum_scalar(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Scalar s = 3.14;
    Matrix m2;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m2 = m1 + s);
    }
    state.SetComplexityN(state.range(0));
}

// Mult two matrices elementwise -----------------------------------------------------------------
template <typename Matrix>
static void mult_two_elwise(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m3 = m1 * m2);
    }
    state.SetComplexityN(state.range(0));
}

// Mult four matrices elementwise -----------------------------------------------------------------
template <typename Matrix>
static void mult_four_elwise(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3 = Matrix::randn(state.range(0), state.range(0));
    Matrix m4 = Matrix::randn(state.range(0), state.range(0));
    Matrix m5;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m5 = m1 * m2 * m3 * m4);
    }
    state.SetComplexityN(state.range(0));
}

// Mult with scalar -----------------------------------------------------------------
template <typename Matrix>
static void mult_scalar(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Scalar s = 3.14;
    Matrix m2;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m2 = m1 * s);
    }
    state.SetComplexityN(state.range(0));
}

// Mult two matrices -----------------------------------------------------------------
template <typename Matrix>
static void mult_two_matrices(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m3 = mat_mult(m1, m2));
    }
    state.SetComplexityN(state.range(0));
}

// Mult four matrices -----------------------------------------------------------------
template <typename Matrix>
static void mult_four_matrices(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3 = Matrix::randn(state.range(0), state.range(0));
    Matrix m4 = Matrix::randn(state.range(0), state.range(0));
    Matrix m5;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m5 = mat_mult(m1, m2, m3, m4));
    }
    state.SetComplexityN(state.range(0));
}

// Mult two epressions -----------------------------------------------------------------
template <typename Matrix>
static void mult_two_expr(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3 = Matrix::randn(state.range(0), state.range(0));
    Matrix m4 = Matrix::randn(state.range(0), state.range(0));
    Matrix m5;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m5 = mat_mult(m1 * m2 + m3 * m4, m2 * m3 - m4 * m1));
    }
    state.SetComplexityN(state.range(0));
}

// Mult two epressions with preeval -----------------------------------------------------------------
template <typename Matrix>
static void mult_two_expr_preeval(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m1 = Matrix::randn(state.range(0), state.range(0));
    Matrix m2 = Matrix::randn(state.range(0), state.range(0));
    Matrix m3 = Matrix::randn(state.range(0), state.range(0));
    Matrix m4 = Matrix::randn(state.range(0), state.range(0));
    Matrix m5;

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(m5 = mat_mult<true>(m1 * m2 + m3 * m4, m2 * m3 - m4 * m1));
    }
    state.SetComplexityN(state.range(0));
}

// LU factorization matrix -----------------------------------------------------------------
template <typename Matrix>
static void LU_factorization(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m = Matrix::randn(state.range(0), state.range(0));
    LinAlg::Solvers::LU lu(m);

    for (auto _ : state)
    {
        lu.reinit(m);
        lu.factorize();
    }
    state.SetComplexityN(state.range(0));
}

// LU solve -----------------------------------------------------------------
template <typename Matrix>
static void LU_solve(benchmark::State& state)
{
    using Scalar = typename Matrix::Scalar;
    Matrix m = Matrix::randn(state.range(0), state.range(0));
    Matrix b = Matrix::randn(state.range(0), 1, -10., 10., 0., 1);
    LinAlg::Solvers::LU lu(m);
    lu.factorize();

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(lu.solve(b));
    }
    state.SetComplexityN(state.range(0));
}
