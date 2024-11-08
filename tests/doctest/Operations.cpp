#include <LinAlg/Matrix.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

TEST_CASE("Matrix Sum")
{
    LinAlg::Matrix<int> m1(2, 3);
    LinAlg::Matrix<int> m2(2, 3);
    LinAlg::Matrix<int> m3(2, 3);
    m1.set(2);
    m2.set(3);
    m3.set(5);

    SUBCASE("two matrices")
    {
        LinAlg::Matrix<int> sum = m1 + m2;

        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
                CHECK_EQ(sum[i, j], m1[i, j] + m2[i, j]);
    }
    SUBCASE("three matrices")
    {
        LinAlg::Matrix<int> sum = m1 + m2 + m3;

        for (int i = 0; i < m1.rows(); ++i)
            for (int j = 0; j < m1.cols(); ++j)
                CHECK_EQ(sum[i, j], m1[i, j] + m2[i, j] + m3[i, j]);
    }
}
