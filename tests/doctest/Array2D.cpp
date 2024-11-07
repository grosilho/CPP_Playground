#include <doctest/doctest.h>
#include <iostream>
#include <string>

import LinAlg.Matrix.Cont;

TEST_CASE("Array2D")
{
    LinAlg::Array2D<double> m1(3, 4);
    CHECK_EQ(m1.rows(), 3);
    CHECK_EQ(m1.cols(), 4);
}

TEST_CASE("Array2D::operator[]")
{
    LinAlg::Array2D<double> m(3, 4);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            m[i, j] = i * m.cols() + j;

    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            CHECK_EQ(m[i, j], i * m.cols() + j);
}
