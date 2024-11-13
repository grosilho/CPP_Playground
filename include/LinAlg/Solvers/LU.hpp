#pragma once

#include <stdafx.hpp>

namespace LinAlg
{
    template <typename Matrix>
    concept MatrixType = requires(Matrix m) {
        { m.rows() } -> std::same_as<int>;
        { m.cols() } -> std::same_as<int>;
        { m[0, 0] } -> std::same_as<typename Matrix::Scalar&>;
    };

    template <MatrixType Matrix>
    class LU
    {
      public:
        LU(const Matrix& m);
        void reinit(const Matrix& m);
        void factorize();
        std::pair<const Matrix&, const Matrix&> getLU() const;
        Matrix solve(const Matrix& b);

      private:
        std::reference_wrapper<const Matrix> m_m;
        Matrix m_l;
        Matrix m_u;
        bool factorized { false };
    };
}

// ------------------------------------------------------------------------------------------------

namespace LinAlg
{
    template <MatrixType Matrix>
    LU<Matrix>::LU(const Matrix& m)
        : m_m(m)
        , m_l(Matrix::Identity(m.rows()))
        , m_u(Matrix::Zero(m.rows(), m.cols()))
    {
        assert(m.rows() == m.cols() && "Matrix must be square.");
    };

    template <MatrixType Matrix>
    void LU<Matrix>::reinit(const Matrix& m)
    {
        m_m = m;
        m_l = Matrix::Identity(m.rows());
        m_u = Matrix::Zero(m.rows(), m.cols());
        factorized = false;
    }

    template <MatrixType Matrix>
    void LU<Matrix>::factorize()
    {
        if (factorized)
            return;

        for (int i = 0; i < m_m.get().rows(); ++i)
        {
            for (int j = i; j < m_m.get().cols(); ++j)
            {
                m_u[i, j] = m_m.get()[i, j];
                for (int k = 0; k < i; ++k)
                    m_u[i, j] -= m_l[i, k] * m_u[k, j];
            }

            for (int j = i + 1; j < m_m.get().rows(); ++j)
            {
                m_l[j, i] = m_m.get()[j, i];
                for (int k = 0; k < i; ++k)
                    m_l[j, i] -= m_l[j, k] * m_u[k, i];
                m_l[j, i] /= m_u[i, i];
            }
        }

        factorized = true;
    }

    template <MatrixType Matrix>
    Matrix LU<Matrix>::solve(const Matrix& b)
    {
        if (!factorized)
            factorize();

        Matrix x = b;
        for (int i = 0; i < m_m.get().rows(); ++i)
            for (int j = 0; j < i; ++j)
                x[i] -= m_l[i, j] * x[j];

        for (int i = m_m.get().rows() - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < m_m.get().rows(); ++j)
                x[i] -= m_u[i, j] * x[j];
            x[i] /= m_u[i, i];
        }

        return std::move(x);
    }

    template <MatrixType Matrix>
    std::pair<const Matrix&, const Matrix&> LU<Matrix>::getLU() const
    {
        return { m_l, m_u };
    }
}
