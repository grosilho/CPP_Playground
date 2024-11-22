#include <backends.hpp>
#include <doctest/doctest.h>

TEST_CASE_TEMPLATE("Constant matrix", S, ET_type<double>)
{
    typename S::Scalar value = 29.12;
    typename S::Constant cte(3, 4, value);
    typename S::Matrix expected(3, 4);
    for (int i = 0; i < cte.rows(); ++i)
        for (int j = 0; j < cte.cols(); ++j)
            expected[i, j] = value;

    CHECK(APPROX_EQ(cte, expected));
}

TEST_CASE_TEMPLATE("Zero matrix", S, ET_type<double>)
{
    typename S::Zero zero(3, 4);
    typename S::Matrix expected(3, 4);
    for (int i = 0; i < zero.rows(); ++i)
        for (int j = 0; j < zero.cols(); ++j)
            expected[i, j] = 0;

    CHECK(APPROX_EQ(zero, expected));
}

TEST_CASE_TEMPLATE("Identity Matrix", S, ET_type<double>)
{
    typename S::Identity identity(3);
    typename S::Matrix expected(3, 3);
    for (int i = 0; i < identity.rows(); ++i)
        for (int j = 0; j < identity.cols(); ++j)
            expected[i, j] = static_cast<typename S::Matrix::Scalar>(i == j);

    CHECK(APPROX_EQ(identity, expected));
}
