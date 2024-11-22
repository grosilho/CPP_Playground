#include <backends.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

TEST_CASE_TEMPLATE("Matrix::shape,rows,cols", Matrix, Common::Matrixd)
{
    Matrix m1(3, 4);
    CHECK_EQ(m1.rows(), 3);
    CHECK_EQ(m1.cols(), 4);
    CHECK_EQ(m1.shape(), std::make_pair<int, int>(3, 4));
    CHECK_EQ(m1.size(), 12);

    Matrix m2(5, 6);
    CHECK_EQ(m2.rows(), 5);
    CHECK_EQ(m2.cols(), 6);
    CHECK_EQ(m2.shape(), std::make_pair<int, int>(5, 6));
    CHECK_EQ(m2.size(), 30);
}

TEST_CASE_TEMPLATE("Matrix::operator[]", Matrix, Common::Matrixi)
{
    Matrix m(3, 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            m[i, j] = i * m.cols() + j;

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
        {
            CHECK_EQ(m[i, j], i * m.cols() + j);
            CHECK_EQ(m[i * m.cols() + j], m[i, j]);
        }
}

TEST_CASE_TEMPLATE("Matrix::Matrix(std::initializer_list)", Matrix, Common::Matrixd)
{
    SUBCASE("3x4")
    {
        Matrix m { { 1., 2., 3. }, { 4., 5., 6. }, { 7., 8., 9. }, { 10., 11., 12. } };
        Matrix expected(4, 3);
        for (int i = 0; i < m.rows(); ++i)
            for (int j = 0; j < m.cols(); ++j)
                expected[i, j] = i * m.cols() + j + 1;

        CHECK(APPROX_EQ(m, expected));
    }
    SUBCASE("5x3")
    {
        Matrix m;
        m = { { 1., 2., 3. }, { 4., 5., 6. }, { 7., 8., 9. }, { 10., 11., 12. }, { 13., 14., 15. } };
        Matrix expected(5, 3);
        for (int i = 0; i < m.rows(); ++i)
            for (int j = 0; j < m.cols(); ++j)
                expected[i, j] = i * m.cols() + j + 1;

        CHECK(APPROX_EQ(m, expected));
    }
}

TEST_CASE_TEMPLATE("Matrix::swap", S, Common_type<int>)
{
    typename S::Matrix m1 { { 9, 6 }, { 2, 3 }, { 2, 6 }, { 2, 5 } };
    typename S::Matrix m2 { { 4, 5, 7, 3, 7, 9, 2 }, { 3, 6, 2, 8, 10, 45, 6 } };
    typename S::Matrix m1_copy(m1);
    typename S::Matrix m2_copy(m2);

    swap(m1, m2);

    CHECK(APPROX_EQ(m1, m2_copy));
    CHECK(APPROX_EQ(m2, m1_copy));
}

TEST_CASE_TEMPLATE("Matrix::copy and move", Matrix, Common::Matrixd)
{
    Matrix m1 { { 2.6, 5.4, 4.7 }, { 8.3, 10.8, 3.4 }, { 9.5, 2.4, 6.9 }, { 7.3, 1.5, 3.6 } };

    SUBCASE("copy constructor")
    {
        Matrix m2(m1);
        CHECK(DEEP_APPROX_EQ(m1, m2));
    }
    SUBCASE("copy assignment")
    {
        Matrix m2(0, 0);
        m2 = m1;
        CHECK(DEEP_APPROX_EQ(m1, m2));
    }
    SUBCASE("move constructor")
    {
        Matrix m1_copy(m1);
        Matrix m2(std::move(m1));
        CHECK_EQ(m1.shape(), std::make_pair<int, int>(0, 0));
        CHECK(DEEP_APPROX_EQ(m1_copy, m2));
    }
    SUBCASE("move assignment")
    {
        Matrix m1_copy(m1);
        Matrix m2(0, 0);
        m2 = std::move(m1);
        CHECK_EQ(m1.shape(), std::make_pair<int, int>(0, 0));
        CHECK(DEEP_APPROX_EQ(m1_copy, m2));
    }
}

TEST_CASE_TEMPLATE("Matrix::copy from different type", S, Common_type<double>)
{
    typename S::Matrix m1 { { 3.23, 9.34, 10.34 }, { 4.23, 9.23, 4.89 } };

    SUBCASE("copy")
    {
        typename S::OtherMatrix m2(m1);
        CHECK(APPROX_EQ(m1, m2));
    }
    SUBCASE("assignment")
    {
        typename S::OtherMatrix m2 = S::OtherMatrix::Zero(m1.rows(), m1.cols());
        m2 = m1;
        CHECK(APPROX_EQ(m1, m2));
    }
}

TEST_CASE_TEMPLATE("Matrix::apply_inplace", Matrix, Common::Matrixd)
{
    using Scalar = Matrix::Scalar;
    const int rows = 4;
    const int cols = 5;
    Matrix m = Matrix::randn(rows, cols);
    Matrix m_copy(m);

    std::function fun = [](Scalar x) { return std::sin(x); };
    m.apply_inplace(fun);

    Matrix expected(rows, cols);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            expected[i, j] = fun(m_copy[i, j]);

    CHECK(APPROX_EQ(m, expected));
}

TEST_CASE_TEMPLATE("Matrix::set", Matrix, Common::Matrixd)
{
    Matrix m(3, 4);
    m.set(42);
    Matrix expeceted(3, 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            expeceted[i, j] = 42;

    CHECK(APPROX_EQ(m, expeceted));
}

TEST_CASE_TEMPLATE("Matrix::Constant", Matrix, Common::Matrixi)
{
    int value = 42;
    Matrix m = Matrix::Constant(3, 4, value);
    Matrix expected(3, 4);
    expected.set(value);

    CHECK(APPROX_EQ(m, expected));
}

TEST_CASE_TEMPLATE("Matrix::Zero", Matrix, Common::Matrixi)
{
    Matrix m = Matrix::Zero(3, 4);
    CHECK_EQ(m.rows(), 3);
    CHECK_EQ(m.cols(), 4);

    Matrix expected(3, 4);
    expected.set(0);
    CHECK(APPROX_EQ(m, expected));
}

TEST_CASE_TEMPLATE("Matrix::Identity", Matrix, Common::Matrixi)
{
    Matrix m = Matrix::Identity(3);
    Matrix expected(3, 3);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            expected[i, j] = static_cast<Matrix::Scalar>(i == j);

    CHECK(APPROX_EQ(m, expected));
}

TEST_CASE_TEMPLATE("Matrix::randn", Matrix, Common::Matrixd)
{
    double min_abs_value = 1.0;
    Matrix m = Matrix::randn(3, 4, 0., 1., min_abs_value);
    CHECK_EQ(m.rows(), 3);
    CHECK_EQ(m.cols(), 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_GE(abs(m[i, j]), min_abs_value);
}
