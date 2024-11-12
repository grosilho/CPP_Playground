#pragma once

#include <LinAlg/Matrix/Derived.hpp>

namespace LinAlg
{
    template <typename LHS, typename RHS, BinaryOp<CommonScalar<LHS, RHS>> BinOp>
    class ElWiseOp : public MatrixBase<ElWiseOp<LHS, RHS, BinOp>>
    {
      public:
        using Scalar = CommonScalar<LHS, RHS>;

        ElWiseOp(const LHS& lhs, const RHS& rhs)
            : MatrixBase<ElWiseOp<LHS, RHS, BinOp>>(lhs.rows(), lhs.cols())
            , m_lhs(lhs)
            , m_rhs(rhs)
        {
        }

        Scalar operator[](int i) const { return BinOp(m_lhs[i], m_rhs[i]); }
        Scalar operator[](int i, int j) const { return BinOp(m_lhs[i, j], m_rhs[i, j]); }

        Matrix<Scalar> eval() const { return Matrix<Scalar>(*this); }

      private:
        typename std::conditional_t<LHS::is_leaf, const LHS&, const LHS> m_lhs;
        typename std::conditional_t<RHS::is_leaf, const RHS&, const RHS> m_rhs;
    };

    namespace Internals
    {
        template <typename T>
        T Sum(const T& lhs, const T& rhs)
        {
            return lhs + rhs;
        }

        template <typename T>
        T Sub(const T& lhs, const T& rhs)
        {
            return lhs - rhs;
        }

        template <typename T>
        T Mul(const T& lhs, const T& rhs)
        {
            return lhs * rhs;
        }

        template <typename T>
        T Div(const T& lhs, const T& rhs)
        {
            return lhs / rhs;
        }
    }

    template <typename LHS, typename RHS>
    ElWiseOp<LHS, RHS, Internals::Sum<CommonScalar<LHS, RHS>>> operator+(const MatrixBase<LHS>& lhs, const MatrixBase<RHS>& rhs)
    {
        return ElWiseOp<LHS, RHS, Internals::Sum<CommonScalar<LHS, RHS>>>(lhs.derived(), rhs.derived());
    }

    template <typename LHS, typename RHS>
    ElWiseOp<LHS, RHS, Internals::Sub<CommonScalar<LHS, RHS>>> operator-(const MatrixBase<LHS>& lhs, const MatrixBase<RHS>& rhs)
    {
        return ElWiseOp<LHS, RHS, Internals::Sub<CommonScalar<LHS, RHS>>>(lhs.derived(), rhs.derived());
    }

    template <typename LHS, typename RHS>
    ElWiseOp<LHS, RHS, Internals::Mul<CommonScalar<LHS, RHS>>> operator*(const MatrixBase<LHS>& lhs, const MatrixBase<RHS>& rhs)
    {
        return ElWiseOp<LHS, RHS, Internals::Mul<CommonScalar<LHS, RHS>>>(lhs.derived(), rhs.derived());
    }

    template <typename LHS, typename RHS>
    ElWiseOp<LHS, RHS, Internals::Div<CommonScalar<LHS, RHS>>> operator/(const MatrixBase<LHS>& lhs, const MatrixBase<RHS>& rhs)
    {
        return ElWiseOp<LHS, RHS, Internals::Div<CommonScalar<LHS, RHS>>>(lhs.derived(), rhs.derived());
    }

}
