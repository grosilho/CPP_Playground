#include <Solvers/Solvers.hpp>
#include <backends.hpp>
#include <doctest/doctest.h>

using LinAlg::Solvers::LU;

TEST_CASE_TEMPLATE("LU", S, ET_type<double>)
{
    SUBCASE("Identity")
    {
        int n = 5;
        typename S::Matrix Id = S::Matrix::Identity(n);
        LU lu(Id);

        lu.factorize();
        auto [L, U] = lu.getLU();

        typename S::Matrix m = mat_mult(L, U);

        CHECK(APPROX_EQ(m, Id));
    }

    SUBCASE("Two random matrices and solver reinit")
    {
        typename S::Matrix m = S::Matrix::randn(5, 5);
        LU lu(m);

        lu.factorize();
        auto [L, U] = lu.getLU();

        typename S::Matrix res = mat_mult(L, U);

        CHECK(APPROX_EQ(m, res));

        m = S::Matrix::randn(20, 20, 10., 100.);
        lu.reinit(m);
        lu.factorize();
        auto [L2, U2] = lu.getLU();
        res = mat_mult(L2, U2);
        CHECK(APPROX_EQ(m, res));
    }

    SUBCASE("Solve")
    {
        typename S::Matrix A = S::Matrix::randn(5, 5);
        typename S::Matrix b1 = S::Matrix::randn(5, 1, -10., 10., 0., 1);
        typename S::Matrix b2 = S::Matrix::randn(5, 1, 10., 10., 0., 2);

        CHECK(!APPROX_EQ(b1, b2));

        LU lu(A);

        typename S::Matrix x1 = lu.solve(b1);
        typename S::Matrix Ax1 = mat_mult(A, x1);
        CHECK(APPROX_EQ(Ax1, b1));

        typename S::Matrix x2 = lu.solve(b2);
        typename S::Matrix Ax2 = mat_mult(A, x2);
        CHECK(APPROX_EQ(Ax2, b2));
    }
}
