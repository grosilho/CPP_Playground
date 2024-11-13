#include <LinAlg/Matrices.hpp>
#include <doctest/doctest.h>

TEST_CASE("Zero matrix")
{
    LinAlg::Zero<int> zero(3, 4);
    CHECK_EQ(zero.rows(), 3);
    CHECK_EQ(zero.cols(), 4);
    CHECK_EQ(zero.size(), 12);

    for (int i = 0; i < zero.rows(); ++i)
        for (int j = 0; j < zero.cols(); ++j)
        {
            CHECK_EQ(zero[i * zero.cols() + j], 0);
            CHECK_EQ(zero[i, j], 0);
        }
}

TEST_CASE("Identity Matrix")
{
    LinAlg::Identity<int> identity(3);
    CHECK_EQ(identity.rows(), 3);
    CHECK_EQ(identity.cols(), 3);
    CHECK_EQ(identity.size(), 9);

    for (int i = 0; i < identity.rows(); ++i)
        for (int j = 0; j < identity.cols(); ++j)
        {
            CHECK_EQ(identity[i * identity.cols() + j], i == j);
            CHECK_EQ(identity[i, j], i == j);
        }
}
