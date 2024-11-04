#include <gtest/gtest.h>

import LinAlg;

TEST (MatrixTests, size_1)
{
    LinAlg::Matrix<double> m (3, 4);
    ASSERT_EQ (m.size ().first, 3);
    ASSERT_EQ (m.size ().second, 4);
    ASSERT_EQ (m.rows (), 3);
    ASSERT_EQ (m.cols (), 4);
}

TEST (MatrixTests, size_2)
{
    LinAlg::Matrix<double> m (5, 6);
    ASSERT_EQ (m.size ().first, 5);
    ASSERT_EQ (m.size ().second, 6);
    ASSERT_EQ (m.rows (), 5);
    ASSERT_EQ (m.cols (), 6);
}
