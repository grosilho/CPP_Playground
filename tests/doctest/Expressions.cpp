#include <LinAlg/Matrices.hpp>
#include <doctest/doctest.h>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

/*
The next two functions perform the same task but with different approaches.
The first one uses a functor to perform the operation, while the second one uses a function.
This is just to try out template template classes (in the first) and variable templates (in the second).
Both use variadic templates to accept any number of matrices.
*/
template <template <typename T> class Fun, typename FirstMat, typename... OtherMats>
void test_el_wise_op_with_functor(FirstMat m1, OtherMats... other_matrices)
{
    using Scalar = typename FirstMat::Scalar;
    Fun<FirstMat> Fun_Mat {};
    Fun<Scalar> Fun_Scalar {};

    auto result = Fun_Mat(m1, other_matrices...);

    FirstMat expected(m1.rows(), m1.cols());
    for (int i = 0; i < m1.size(); i++)
        expected[i] = Fun_Scalar(m1[i], other_matrices[i]...);

    CHECK(LinAlg::APPROX_EQ(result, expected));
}

// Unfortunately variable templates cannot be used as template template parameters, so we need to pass the function twice, once for the matrices and once for the scalars.
template <typename FunMat, typename FunScalar, typename FirstMat, typename... OtherMats>
void test_el_wise_op_with_function(FunMat fun_mat, FunScalar fun_scalar, FirstMat m1, OtherMats... other_matrices)
{
    auto result = fun_mat(m1, other_matrices...);

    FirstMat expected(m1.rows(), m1.cols());
    for (int i = 0; i < m1.size(); i++)
        expected[i] = fun_scalar(m1[i], other_matrices[i]...);

    CHECK(LinAlg::APPROX_EQ(result, expected));
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

// The functions below are used to test more complex element wise operations.
template <class T>
std::function<T(T&, T&, T&)> test_composition_1 = [](T& a, T& b, T& c) { return a + b * c; };
template <class T>
std::function<T(T&, T&, T&)> test_composition_2 = [](T& a, T& b, T& c) { return a / c + b; };
template <class T>
std::function<T(T&, T&, T&)> test_composition_3 = [](T& a, T& b, T& c) { return (a * c + b / c) * c + a - b; };

TEST_CASE("Matrix element wise operations")
{
    using Scalar = double;
    using Mat = LinAlg::Matrix<Scalar>;
    int rows = 5;
    int cols = 7;
    Mat m1 = LinAlg::Matrix<Scalar>::randn(rows, cols, 0., 1., 1e-8);
    Mat m2 = LinAlg::Matrix<Scalar>::randn(rows, cols, 0., 1., 1e-8);
    Mat m3 = LinAlg::Matrix<Scalar>::randn(rows, cols, 0., 1., 1e-8);

    SUBCASE("sum two matrices") { test_el_wise_op_with_functor<test_sum>(m1, m2); }
    SUBCASE("sum three matrices") { test_el_wise_op_with_functor<test_sum>(m1, m2, m3); }
    SUBCASE("diff two matrices") { test_el_wise_op_with_functor<test_diff>(m1, m2); }
    SUBCASE("diff three matrices") { test_el_wise_op_with_functor<test_diff>(m1, m2, m3); }
    SUBCASE("mult two matrices") { test_el_wise_op_with_functor<test_mult>(m1, m2); }
    SUBCASE("mult three matrices") { test_el_wise_op_with_functor<test_mult>(m1, m2, m3); }
    SUBCASE("div two matrices") { test_el_wise_op_with_functor<test_div>(m1, m2); }
    SUBCASE("div three matrices") { test_el_wise_op_with_functor<test_div>(m1, m2, m3); }

    SUBCASE("temporary object")
    {
        using LinAlg::Matrix;

        auto sum(m1 + (m2 + m3));
        for (int i = 0; i < m1.rows() * m1.cols(); ++i)
            CHECK(sum[i] == doctest::Approx(m1[i] + m2[i] + m3[i]).epsilon(1e-10));
    }

    SUBCASE("composition 1") { test_el_wise_op_with_function(test_composition_1<Mat>, test_composition_1<Scalar>, m1, m2, m3); }
    SUBCASE("composition 2") { test_el_wise_op_with_function(test_composition_2<Mat>, test_composition_2<Scalar>, m1, m2, m3); }
    SUBCASE("composition 3") { test_el_wise_op_with_function(test_composition_3<Mat>, test_composition_3<Scalar>, m1, m2, m3); }

    SUBCASE("matrix + scalar")
    {
        Scalar scalar = 3.14;
        auto sum = m1 + scalar;
        for (int i = 0; i < m1.rows() * m1.cols(); ++i)
            CHECK(sum[i] == doctest::Approx(m1[i] + scalar).epsilon(1e-10));
    }

    SUBCASE("operations with zero")
    {
        LinAlg::Zero<Scalar> zero(rows, cols);
        Mat sum = m1 + zero;
        CHECK(LinAlg::APPROX_EQ(sum, m1));

        Mat mult = m1 * zero;
        CHECK(LinAlg::APPROX_EQ(mult, zero));

        Mat div = zero / m1;
        CHECK(LinAlg::APPROX_EQ(div, zero));
    }

    SUBCASE("sum with identity")
    {
        Mat m = LinAlg::Matrix<Scalar>::randn(rows, rows);
        LinAlg::Identity<Scalar> id(rows);
        Mat sum = m + id;
        for (int i = 0; i < m.rows() * m.cols(); ++i)
            CHECK(sum[i] == doctest::Approx(m[i] + (i / m.cols() == i % m.cols())).epsilon(1e-10));

        Mat mult = m * id;
        for (int i = 0; i < m.rows() * m.cols(); ++i)
            CHECK(mult[i] == doctest::Approx(m[i] * (i / m.cols() == i % m.cols())).epsilon(1e-10));

        Mat div = id / m;
        for (int i = 0; i < m.rows() * m.cols(); ++i)
            CHECK(div[i] == doctest::Approx((i / m.cols() == i % m.cols()) / m[i]).epsilon(1e-10));
    }
}

template <typename A, typename B>
auto getMatMultCoeff(const A& lhs, const B& rhs, int i, int j)
{
    using T = LinAlg::_implementation_details::CommonScalar<A, B>;
    T result = lhs[i, 0] * rhs[0, j];
    for (int k = 1; k < lhs.cols(); ++k)
        result += lhs[i, k] * rhs[k, j];
    return result;
}

template <typename A, typename B>
auto multiply_by_hand(const A& lhs, const B& rhs)
{
    using T = LinAlg::_implementation_details::CommonScalar<A, B>;
    LinAlg::Matrix<T> result(lhs.rows(), rhs.cols());
    for (int i = 0; i < lhs.rows(); ++i)
        for (int j = 0; j < rhs.cols(); ++j)
            result[i, j] = getMatMultCoeff(lhs, rhs, i, j);
    return result;
}

TEST_CASE("Matrix-Matrix multiplication")
{
    using Scalar = double;
    using Mat = LinAlg::Matrix<Scalar>;
    int n1 = 12;
    int n2 = 6;
    int n3 = 18;
    int n4 = 8;
    Mat m1a = LinAlg::Matrix<Scalar>::randn(n1, n2, 0., 1., 1e-8);
    Mat m2a = LinAlg::Matrix<Scalar>::randn(n2, n3, 0., 1., 1e-8);

    SUBCASE("simple matrix-matrix")
    {
        Mat result = mat_mult(m1a, m2a);

        CHECK(result.rows() == n1);
        CHECK(result.cols() == n3);

        Mat expected = multiply_by_hand(m1a, m2a);
        CHECK(LinAlg::APPROX_EQ(result, expected));
    }
    SUBCASE("matrix-matrix of expressions")
    {
        Mat m1b = LinAlg::Matrix<Scalar>::randn(n1, n2, 0., 1., 1e-8);
        Mat m2b = LinAlg::Matrix<Scalar>::randn(n2, n3, 0., 1., 1e-8);
        SUBCASE("sum and diff")
        {
            Mat result = mat_mult(m1a + m1b, m2a - m2b);
            CHECK(result.rows() == n1);
            CHECK(result.cols() == n3);

            Mat lhs = m1a + m1b;
            Mat rhs = m2a - m2b;
            Mat expected = multiply_by_hand(lhs, rhs);
            CHECK(LinAlg::APPROX_EQ(result, expected));
        }
        SUBCASE("mult and div with pre evaluation")
        {
            Mat result = mat_mult<true>(m1a * m1b, m2a / m2b);
            CHECK(result.rows() == n1);
            CHECK(result.cols() == n3);

            Mat lhs = m1a * m1b;
            Mat rhs = m2a / m2b;
            Mat expected = multiply_by_hand(lhs, rhs);
            CHECK(LinAlg::APPROX_EQ(result, expected));
        }
    }
    SUBCASE("multiple matrices")
    {
        Mat m1b = LinAlg::Matrix<Scalar>::randn(n1, n2, 0., 1., 1e-8);
        Mat m2b = LinAlg::Matrix<Scalar>::randn(n2, n3, 0., 1., 1e-8);
        Mat m3a = LinAlg::Matrix<Scalar>::randn(n3, n4, 0., 1., 1e-8);
        Mat m3b = LinAlg::Matrix<Scalar>::randn(n3, n4, 0., 1., 1e-8);

        SUBCASE("three matrices")
        {
            Mat result = mat_mult(m1a, m2a, m3a);
            CHECK(result.rows() == n1);
            CHECK(result.cols() == n4);

            Mat expected = multiply_by_hand(multiply_by_hand(m1a, m2a), m3a);
            CHECK(LinAlg::APPROX_EQ(result, expected));
        }

        SUBCASE("three matrices with expressions and pre evaluation")
        {
            Mat result = mat_mult<true>(m1a + m1b, m2a - m2b, m3a * m3b);
            CHECK(result.rows() == n1);
            CHECK(result.cols() == n4);

            Mat expected = multiply_by_hand(multiply_by_hand(m1a + m1b, m2a - m2b), m3a * m3b);
            CHECK(LinAlg::APPROX_EQ(result, expected));
        }
    }
}
