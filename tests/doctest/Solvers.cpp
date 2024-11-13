#include <LinAlg/Matrices.hpp>
#include <LinAlg/Solvers.hpp>
#include <doctest/doctest.h>

TEST_CASE("LU")
{
    using Matrix = LinAlg::Matrix<double>;

    SUBCASE("Identity")
    {
        int n = 5;
        Matrix Id = Matrix::Identity(n);
        LinAlg::LU lu(Id);

        lu.factorize();
        auto [L, U] = lu.getLU();

        Matrix m = LinAlg::mat_mult(L, U);

        CHECK(LinAlg::APPROX_EQ(m, Id));
    }

    SUBCASE("Two random matrices and solver reinit")
    {
        Matrix m = Matrix::randn(5, 5);
        LinAlg::LU lu(m);

        lu.factorize();
        auto [L, U] = lu.getLU();

        Matrix res = LinAlg::mat_mult(L, U);

        CHECK(LinAlg::APPROX_EQ(m, res));

        m = Matrix::randn(20, 20, 10., 100.);
        lu.reinit(m);
        lu.factorize();
        auto [L2, U2] = lu.getLU();
        res = LinAlg::mat_mult(L2, U2);
        CHECK(LinAlg::APPROX_EQ(m, res));
    }

    SUBCASE("Solve")
    {
        Matrix A = Matrix::randn(5, 5);
        Matrix b1 = Matrix::randn(5, 1);
        Matrix b2 = Matrix::randn(5, 1);

        LinAlg::LU lu(A);

        Matrix x1 = lu.solve(b1);
        Matrix Ax1 = LinAlg::mat_mult(A, x1);
        CHECK(LinAlg::APPROX_EQ(Ax1, b1));

        Matrix x2 = lu.solve(b2);
        Matrix Ax2 = LinAlg::mat_mult(A, x2);
        CHECK(LinAlg::APPROX_EQ(Ax2, b2));
    }
}
