#include <LinAlg/Matrices.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

TEST_CASE("Matrix::shape,rows,cols")
{
    LinAlg::Matrix<double> m1(3, 4);
    CHECK_EQ(m1.rows(), 3);
    CHECK_EQ(m1.cols(), 4);
    CHECK_EQ(m1.shape(), std::make_pair<int, int>(3, 4));
    CHECK_EQ(m1.size(), 12);

    LinAlg::Matrix<double> m2(5, 6);
    CHECK_EQ(m2.rows(), 5);
    CHECK_EQ(m2.cols(), 6);
    CHECK_EQ(m2.shape(), std::make_pair<int, int>(5, 6));
    CHECK_EQ(m2.size(), 30);
}

TEST_CASE("Matrix::operator[]")
{
    LinAlg::Matrix<double> m(3, 4);
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

TEST_CASE("Matrix::Matrix(std::initializer_list)")
{
    LinAlg::Matrix<int> m { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };
    CHECK_EQ(m.rows(), 4);
    CHECK_EQ(m.cols(), 3);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_EQ(m[i, j], i * m.cols() + j + 1);

    LinAlg::Matrix<int> m2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 }, { 13, 14, 15 } };
    CHECK_EQ(m2.rows(), 5);
    CHECK_EQ(m2.cols(), 3);
    for (int i = 0; i < m2.rows(); ++i)
        for (int j = 0; j < m2.cols(); ++j)
            CHECK_EQ(m2[i, j], i * m2.cols() + j + 1);
}

TEST_CASE("Matrix::copy and move")
{
    LinAlg::Matrix<int> m1 { { 2, 5, 4 }, { 8, 10, 3 }, { 9, 2, 6 }, { 7, 1, 3 } };

    SUBCASE("copy constructor")
    {
        LinAlg::Matrix<int> m2(m1);
        CHECK_EQ(m1.shape(), m2.shape());
        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
            {
                CHECK_EQ(m2[i, j], m1[i, j]);
                CHECK_EQ(m2[i * m2.cols() + j], m2[i, j]);
            }
    }
    SUBCASE("copy assignment")
    {
        LinAlg::Matrix<int> m2(0, 0);
        m2 = m1;
        CHECK_EQ(m1.shape(), m2.shape());
        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
            {
                CHECK_EQ(m2[i, j], m1[i, j]);
                CHECK_EQ(m2[i * m2.cols() + j], m2[i, j]);
            }
    }
    SUBCASE("move constructor")
    {
        LinAlg::Matrix<int> m1_copy(m1);
        LinAlg::Matrix<int> m2(std::move(m1));
        CHECK_EQ(m1.shape(), std::make_pair<int, int>(0, 0));
        CHECK_EQ(m1_copy.shape(), m2.shape());
        for (int i = 0; i < m1_copy.rows(); ++i)
            for (int j = 0; j < m1_copy.cols(); ++j)
            {
                CHECK_EQ(m2[i, j], m1_copy[i, j]);
                CHECK_EQ(m2[i * m2.cols() + j], m2[i, j]);
            }
    }
    SUBCASE("move assignment")
    {
        LinAlg::Matrix<int> m1_copy(m1);
        LinAlg::Matrix<int> m2(0, 0);
        m2 = std::move(m1);
        CHECK_EQ(m1.shape(), std::make_pair<int, int>(0, 0));
        CHECK_EQ(m1_copy.shape(), m2.shape());
        for (int i = 0; i < m1_copy.rows(); ++i)
            for (int j = 0; j < m1_copy.cols(); ++j)
            {
                CHECK_EQ(m2[i, j], m1_copy[i, j]);
                CHECK_EQ(m2[i * m2.cols() + j], m2[i, j]);
            }
    }
}

TEST_CASE("Matrix::Identity")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Identity(3);
    CHECK_EQ(m.rows(), 3);
    CHECK_EQ(m.cols(), 3);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_EQ(m[i, j], i == j);
}

TEST_CASE("Matrix::Zero")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Zero(3, 4);
    CHECK_EQ(m.rows(), 3);
    CHECK_EQ(m.cols(), 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_EQ(m[i, j], 0);
}

TEST_CASE("Matrix::randn")
{
    double min_abs_value = 1.0;
    LinAlg::Matrix<double> m = LinAlg::Matrix<double>::randn(3, 4, 0., 1., min_abs_value);
    CHECK_EQ(m.rows(), 3);
    CHECK_EQ(m.cols(), 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_GE(abs(m[i, j]), min_abs_value);
}

TEST_CASE("Matrix::swap")
{
    LinAlg::Matrix<double> m1 { { 9, 6 }, { 2, 3 }, { 2, 6 }, { 2, 5 } };
    LinAlg::Matrix<double> m2 { { 4, 5, 7, 3, 7, 9, 2 }, { 3, 6, 2, 8, 10, 45, 6 } };
    LinAlg::Matrix<double> m1_copy(m1);
    LinAlg::Matrix<double> m2_copy(m2);

    LinAlg::swap(m1, m2);

    CHECK_EQ(m1.shape(), m2_copy.shape());
    CHECK(LinAlg::APPROX_EQ(m1, m2_copy));

    CHECK_EQ(m2.shape(), m1_copy.shape());
    CHECK(LinAlg::APPROX_EQ(m2, m1_copy));
}

TEST_CASE("Matrix::set")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Zero(3, 4);
    m.set(42);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
        {
            CHECK_EQ(m[i, j], 42);
            CHECK_EQ(m[i * m.cols() + j], 42);
        }
}

TEST_CASE("Matrix::zero")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Identity(3);
    m.zero();
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_EQ(m[i, j], 0);
}

TEST_CASE("Matrix::apply")
{
    LinAlg::Matrix<double> m { { 3.23, 5.453, 9.243 }, { 4.23, 9.23, 4.89 } };

    std::function cos = [](double i) { return std::cos(i); };
    LinAlg::Matrix<double> cos_m = m.apply(cos);

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK(cos_m[i, j] == doctest::Approx(std::cos(m[i, j])).epsilon(1e-12));
}

TEST_CASE("Matrix::apply_inplace")
{
    LinAlg::Matrix<double> m { { 1.23, 3.54, 2.64, 90.45 }, { 3.23, 5.453, 9.243, 4.23 }, { 9.73, 4.89, 3.23, 5.453 } };
    LinAlg::Matrix<double> m_copy(m);

    std::function sin = [](double i) { return std::sin(i); };
    m.apply_inplace(sin);

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK(m[i, j] == doctest::Approx(std::sin(m_copy[i, j])).epsilon(1e-12));
}

TEST_CASE("Matrix::copy from different type")
{
    LinAlg::Matrix<double> m1 { { 3.23, 9.34, 10.34 }, { 4.23, 9.23, 4.89 } };

    SUBCASE("copy")
    {
        LinAlg::Matrix<int> m2(m1);

        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
                CHECK_EQ(m2[i, j], static_cast<int>(m1[i, j]));
    }
    SUBCASE("assignment")
    {
        LinAlg::Matrix<int> m2 = LinAlg::Matrix<int>::Zero(m1.rows(), m1.cols());
        m2 = m1;

        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
                CHECK_EQ(m2[i, j], static_cast<int>(m1[i, j]));
    }
}
