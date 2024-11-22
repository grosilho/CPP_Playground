#include <backends.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

TEST_CASE_TEMPLATE("Matrix::apply", Matrix, ET::Matrixd)
{
    using Scalar = Matrix::Scalar;
    const int rows = 4;
    const int cols = 5;
    Matrix m = Matrix::randn(rows, cols);

    Scalar (&std_fun)(Scalar) = std::cos;

    Matrix expected(rows, cols);
    for (int i = 0; i < m.rows(); ++i)
        for (int j = 0; j < m.cols(); ++j)
            expected[i, j] = std_fun(m[i, j]);

    SUBCASE("with function pointer")
    {
        Matrix fun_m = m.apply(std_fun);
        CHECK(APPROX_EQ(fun_m, expected));
    }

    SUBCASE("with std::function")
    {
        std::function fun { std_fun };

        SUBCASE("with std::function as lvalue")
        {
            Matrix fun_m = m.apply(fun);
            CHECK(APPROX_EQ(fun_m, expected));
        }
        SUBCASE("with std::function as rvalue")
        {
            Matrix fun_m = m.apply(std::move(fun));
            CHECK(APPROX_EQ(fun_m, expected));
        }
    }

    SUBCASE("with lambda expression")
    {
        Matrix fun_m = m.apply([](Scalar x) { return std_fun(x); });
        CHECK(APPROX_EQ(fun_m, expected));
    }
}
