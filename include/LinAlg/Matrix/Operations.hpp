#pragma once

#include <LinAlg/Matrix/Base.hpp>

namespace LinAlg
{
    template <typename LHS, typename RHS>
    class MatrixSum : public MatrixBase<MatrixSum<LHS, RHS>>
    {
      public:
        using Scalar = std::common_type_t<typename LHS::Scalar, typename RHS::Scalar>;

        MatrixSum(const LHS& lhs, const RHS& rhs)
            : MatrixBase<MatrixSum<LHS, RHS>>(lhs.rows(), lhs.cols())
            , m_lhs(lhs)
            , m_rhs(rhs)
        {
        }

        Scalar operator[](int i) const { return m_lhs[i] + m_rhs[i]; }

      private:
        const LHS& m_lhs;
        const RHS& m_rhs;
    };

    template <typename LHS, typename RHS>
    MatrixSum<LHS, RHS> operator+(const MatrixBase<LHS>& lhs, const MatrixBase<RHS>& rhs)
    {
        return MatrixSum<LHS, RHS>(lhs.derived(), rhs.derived());
    }
}
