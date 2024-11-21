#include <backends.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>
#include <vector>

/*
 Helper function to test element wise operations with functors.
*/
template <template <typename T> class Fun, typename FirstMat, typename... OtherMats>
void test_el_wise_op(FirstMat m1, OtherMats... other_matrices)
{
    using Scalar = typename FirstMat::Scalar;
    Fun<FirstMat> Fun_Mat {};
    Fun<Scalar> Fun_Scalar {};

    auto result = Fun_Mat(m1, other_matrices...);

    FirstMat expected(m1.rows(), m1.cols());
    for (int i = 0; i < m1.size(); i++)
        expected[i] = Fun_Scalar(m1[i], other_matrices[i]...);

    CHECK(APPROX_EQ(result, expected));
}

// The functors below are used to test the element wise operations.
template <typename T>
struct test_sum
{
    template <typename... Args>
    T operator()(Args&... args)
    {
        return (args + ...);
    }
};
template <typename T>
struct test_diff
{
    template <typename... Args>
    T operator()(Args&... args)
    {
        return (args - ...); // equivalent to: (A1 - (A2 - (A3-...))). Ex: (A1 - (A2 - (A3 - A4))) = A1 - A2 + A3 - A4
    }
};
template <typename T>
struct test_mult
{
    template <typename... Args>
    T operator()(Args&... args)
    {
        return (args * ...);
    }
};
template <typename T>
struct test_div
{
    template <typename... Args>
    T operator()(Args&... args)
    {
        return (args / ...);
    }
};
template <typename T>
struct test_composition_1
{
    T operator()(T& a, T& b, T& c) { return a + b * c; };
};
template <typename T>
struct test_composition_2
{
    T operator()(T& a, T& b, T& c) { return a / c + b; };
};
template <typename T>
struct test_composition_3
{
    T operator()(T& a, T& b, T& c) { return (a * c + b / c) * c + a - b; };
};

TEST_CASE_TEMPLATE("Matrix element wise operations", S, ET_CRTP_type<double>)
{
    using Scalar = S::Scalar;
    using Matrix = S::Matrix;

    int rows = 5;
    int cols = 7;
    Matrix m1 = Matrix::randn(rows, cols, 0., 1., 1e-8);
    Matrix m2 = Matrix::randn(rows, cols, 0., 1., 1e-8);
    Matrix m3 = Matrix::randn(rows, cols, 0., 1., 1e-8);

    SUBCASE("sum two matrices") { test_el_wise_op<test_sum>(m1, m2); }
    SUBCASE("sum three matrices") { test_el_wise_op<test_sum>(m1, m2, m3); }
    SUBCASE("diff two matrices") { test_el_wise_op<test_diff>(m1, m2); }
    SUBCASE("diff three matrices") { test_el_wise_op<test_diff>(m1, m2, m3); }
    SUBCASE("mult two matrices") { test_el_wise_op<test_mult>(m1, m2); }
    SUBCASE("mult three matrices") { test_el_wise_op<test_mult>(m1, m2, m3); }
    SUBCASE("div two matrices") { test_el_wise_op<test_div>(m1, m2); }
    SUBCASE("div three matrices") { test_el_wise_op<test_div>(m1, m2, m3); }
    SUBCASE("composition 1") { test_el_wise_op<test_composition_1>(m1, m2, m3); }
    SUBCASE("composition 2") { test_el_wise_op<test_composition_2>(m1, m2, m3); }
    SUBCASE("composition 3") { test_el_wise_op<test_composition_3>(m1, m2, m3); }

    SUBCASE("temporary object")
    {
        auto sum(m1 + (m2 + m3));
        Matrix expected(rows, cols);
        for (int i = 0; i < m1.rows() * m1.cols(); ++i)
            expected[i] = m1[i] + m2[i] + m3[i];

        CHECK(APPROX_EQ(sum, expected));
    }

    SUBCASE("matrix + scalar")
    {
        Scalar scalar = 3.14;
        auto sum = m1 + scalar;
        Matrix expected(rows, cols);
        for (int i = 0; i < m1.rows() * m1.cols(); ++i)
            expected[i] = m1[i] + scalar;
        CHECK(APPROX_EQ(sum, expected));
    }

    SUBCASE("operations with zero")
    {
        typename S::Zero zero(rows, cols);
        Matrix sum = m1 + zero;
        CHECK(APPROX_EQ(sum, m1));

        Matrix mult = m1 * zero;
        CHECK(APPROX_EQ(mult, zero));

        Matrix div = zero / m1;
        CHECK(APPROX_EQ(div, zero));
    }

    SUBCASE("operations with identity")
    {
        typename S::Identity id(rows);
        Matrix m = Matrix::randn(rows, rows);

        SUBCASE("sum")
        {
            Matrix sum = m + id;
            Matrix expected(rows, rows);
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < rows; ++j)
                    expected[i, j] = m[i, j] + (i == j);
            CHECK(APPROX_EQ(sum, expected));
        }

        SUBCASE("mult")
        {
            Matrix mult = m * id;
            Matrix expected(rows, rows);
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < rows; ++j)
                    expected[i, j] = m[i, j] * (i == j);
            CHECK(APPROX_EQ(mult, expected));
        }

        SUBCASE("div")
        {
            Matrix div = id / m;
            Matrix expected(rows, rows);
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < rows; ++j)
                    expected[i, j] = (i == j) / m[i, j];
            CHECK(APPROX_EQ(div, expected));
        }
    }
}

/*
 Two helper functions to test the matrix-matrix multiplication.
*/
template <typename A, typename B>
auto getMatMultCoeff(const A& lhs, const B& rhs, int i, int j)
{
    using T = std::common_type_t<typename A::Scalar, typename B::Scalar>;
    T result = lhs[i, 0] * rhs[0, j];
    for (int k = 1; k < lhs.cols(); ++k)
        result += lhs[i, k] * rhs[k, j];
    return result;
}

template <typename ResType, typename A, typename B>
auto multiply_by_hand(const A& lhs, const B& rhs)
{
    ResType result(lhs.rows(), rhs.cols());
    for (int i = 0; i < lhs.rows(); ++i)
        for (int j = 0; j < rhs.cols(); ++j)
            result[i, j] = getMatMultCoeff(lhs, rhs, i, j);
    return result;
}

TEST_CASE_TEMPLATE("Matrix-Matrix multiplication", S, ET_CRTP_type<double>)
{
    using Matrix = S::Matrix;

    int n1 = 12;
    int n2 = 6;
    int n3 = 18;
    int n4 = 8;
    Matrix m1a = Matrix::randn(n1, n2, 0., 1., 1e-8);
    Matrix m2a = Matrix::randn(n2, n3, 0., 1., 1e-8);

    SUBCASE("simple matrix-matrix")
    {
        Matrix result = mat_mult(m1a, m2a);
        Matrix expected = multiply_by_hand<Matrix>(m1a, m2a);
        CHECK(DEEP_APPROX_EQ(result, expected));
    }
    SUBCASE("matrix-matrix of expressions")
    {
        Matrix m1b = Matrix::randn(n1, n2, 0., 1., 1e-8);
        Matrix m2b = Matrix::randn(n2, n3, 0., 1., 1e-8);
        SUBCASE("sum and diff")
        {
            Matrix result = mat_mult(m1a + m1b, m2a - m2b);
            Matrix lhs = m1a + m1b;
            Matrix rhs = m2a - m2b;
            Matrix expected = multiply_by_hand<Matrix>(lhs, rhs);
            CHECK(DEEP_APPROX_EQ(result, expected));
        }
        SUBCASE("mult and div with pre evaluation")
        {
            Matrix result = mat_mult<true>(m1a * m1b, m2a / m2b);
            Matrix lhs = m1a * m1b;
            Matrix rhs = m2a / m2b;
            Matrix expected = multiply_by_hand<Matrix>(lhs, rhs);
            CHECK(DEEP_APPROX_EQ(result, expected));
        }
    }
    SUBCASE("multiple matrices")
    {
        Matrix m1b = Matrix::randn(n1, n2, 0., 1., 1e-8);
        Matrix m2b = Matrix::randn(n2, n3, 0., 1., 1e-8);
        Matrix m3a = Matrix::randn(n3, n4, 0., 1., 1e-8);
        Matrix m3b = Matrix::randn(n3, n4, 0., 1., 1e-8);

        SUBCASE("three matrices")
        {
            Matrix result = mat_mult(m1a, m2a, m3a);
            Matrix expected = multiply_by_hand<Matrix>(multiply_by_hand<Matrix>(m1a, m2a), m3a);
            CHECK(DEEP_APPROX_EQ(result, expected));
        }

        SUBCASE("three matrices with expressions and pre evaluation")
        {
            Matrix result = mat_mult<true>(m1a + m1b, m2a - m2b, m3a * m3b);
            Matrix expected = multiply_by_hand<Matrix>(multiply_by_hand<Matrix>(m1a + m1b, m2a - m2b), m3a * m3b);
            CHECK(DEEP_APPROX_EQ(result, expected));
        }
    }
}
