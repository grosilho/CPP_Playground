#include <LinAlg/Matrix.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

template <typename T>
LinAlg::Matrix<T> createMatrix(int rows, int cols)
{
    LinAlg::Matrix<T> m(rows, cols);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            m[i, j] = i * m.cols() + j;
    return m;
}

TEST_CASE("Matrix::size,rows,cols")
{
    LinAlg::Matrix<double> m1(3, 4);
    CHECK_EQ(m1.rows(), 3);
    CHECK_EQ(m1.cols(), 4);
    CHECK_EQ(m1.size(), std::make_pair<int, int>(3, 4));

    LinAlg::Matrix<double> m2(5, 6);
    CHECK_EQ(m2.rows(), 5);
    CHECK_EQ(m2.cols(), 6);
    CHECK_EQ(m2.size(), std::make_pair<int, int>(5, 6));
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

TEST_CASE("Matrix::copy and move")
{
    LinAlg::Matrix<int> m1(3, 4);
    for (int i = 0; i < m1.rows(); ++i)
        for (int j = 0; j < m1.cols(); ++j)
            m1[i, j] = i * m1.cols() + j;

    SUBCASE("copy constructor")
    {
        LinAlg::Matrix<int> m2(m1);
        CHECK_EQ(m1.size(), m2.size());
        CHECK_EQ(m1.rows(), m2.rows());
        CHECK_EQ(m1.cols(), m2.cols());
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
        CHECK_EQ(m1.size(), m2.size());
        CHECK_EQ(m1.rows(), m2.rows());
        CHECK_EQ(m1.cols(), m2.cols());
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
        CHECK_EQ(m1.size(), std::make_pair<int, int>(0, 0));
        CHECK_EQ(m1.rows(), 0);
        CHECK_EQ(m1.cols(), 0);
        CHECK_EQ(m1_copy.size(), m2.size());
        CHECK_EQ(m1_copy.rows(), m2.rows());
        CHECK_EQ(m1_copy.cols(), m2.cols());
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
        CHECK_EQ(m1.size(), std::make_pair<int, int>(0, 0));
        CHECK_EQ(m1.rows(), 0);
        CHECK_EQ(m1.cols(), 0);
        CHECK_EQ(m1_copy.size(), m2.size());
        CHECK_EQ(m1_copy.rows(), m2.rows());
        CHECK_EQ(m1_copy.cols(), m2.cols());
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

TEST_CASE("Matrix::swap")
{
    LinAlg::Matrix<double> m1 = createMatrix<double>(3, 4);
    LinAlg::Matrix<double> m2 = createMatrix<double>(5, 6);
    LinAlg::Matrix<double> m1_copy(m1);
    LinAlg::Matrix<double> m2_copy(m2);

    LinAlg::swap(m1, m2);

    CHECK_EQ(m1.size(), m2_copy.size());
    CHECK_EQ(m1.rows(), m2_copy.rows());
    CHECK_EQ(m1.cols(), m2_copy.cols());
    for (int i = 0; i < m1.rows(); ++i)
        for (int j = 0; j < m1.cols(); ++j)
        {
            CHECK(m1[i, j] == doctest::Approx(m2_copy[i, j]).epsilon(1e-12));
            CHECK(m1[i * m1.cols() + j] == doctest::Approx(m1[i, j]).epsilon(1e-12));
        }

    CHECK_EQ(m2.size(), m1_copy.size());
    CHECK_EQ(m2.rows(), m1_copy.rows());
    CHECK_EQ(m2.cols(), m1_copy.cols());
    for (int i = 0; i < m2.rows(); ++i)
        for (int j = 0; j < m2.cols(); ++j)
        {
            CHECK(m2[i, j] == doctest::Approx(m1_copy[i, j]).epsilon(1e-12));
            CHECK(m2[i * m2.cols() + j] == doctest::Approx(m2[i, j]).epsilon(1e-12));
        }
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
    LinAlg::Matrix<double> m = createMatrix<double>(3, 8);

    std::function cos = [](double i) { return std::cos(i); };
    LinAlg::Matrix<double> cos_m = m.apply(cos);

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK(cos_m[i, j] == doctest::Approx(std::cos(m[i, j])).epsilon(1e-12));
}

TEST_CASE("Matrix::apply_inplace")
{
    LinAlg::Matrix<double> m = createMatrix<double>(3, 8);
    LinAlg::Matrix<double> m_copy(m);

    std::function sin = [](double i) { return std::sin(i); };
    m.apply_inplace(sin);

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK(m[i, j] == doctest::Approx(std::sin(m_copy[i, j])).epsilon(1e-12));
}

TEST_CASE("Matrix::copy from different type")
{
    LinAlg::Matrix<double> m1 = createMatrix<double>(3, 8);

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
