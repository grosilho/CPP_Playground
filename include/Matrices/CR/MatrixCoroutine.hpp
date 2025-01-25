#pragma once

#include <Matrices/CR/ForwardDeclarations.hpp>
#include <Matrices/Common/Base.hpp>

namespace LinAlg::Matrices::CR
{
    template <typename CoroutineType>
    class MatrixCoroutine : public MatrixBase<MatrixCoroutine<CoroutineType>>
    {
      public:
        using Scalar = LinAlg::traits<CoroutineType>::Scalar;

        template <typename CT>
        MatrixCoroutine(int rows, int cols, CT&& coroutine)
            : MatrixBase<MatrixCoroutine<CoroutineType>>(rows, cols)
            , m_coroutine(std::move<CT>(coroutine)) // coroutines are moved. Copy needs more care
        {
        }

        Matrix<Scalar> eval() const { return Matrix<Scalar>(*this); }

        Scalar operator[](int i, int j) const { return m_coroutine[i * this->m_cols + j]; }; ///< Access the element at row i and column j.
        Scalar operator[](int i) const { return m_coroutine[i]; };                           ///< Access the element i in the flattened matrix.

      private:
        CoroutineType m_coroutine;
    };

    template <typename CR>
    MatrixCoroutine(int, int, CR&&) -> MatrixCoroutine<std::remove_cvref_t<CR>>;
}
