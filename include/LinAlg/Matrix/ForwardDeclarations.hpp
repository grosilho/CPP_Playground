#pragma once

namespace LinAlg
{
    template <typename T>
    using BinaryOp = T (*)(const T&, const T&);

    template <typename LHS, typename RHS>
    using CommonScalar = std::common_type_t<typename LHS::Scalar, typename RHS::Scalar>;

    template <typename Derived>
    class MatrixBase;

    template <typename T>
    class Matrix;

    template <typename LHS, typename RHS, BinaryOp<CommonScalar<LHS, RHS>> BinOp>
    class ElWiseOp;

    template <typename T>
    struct traits;

    template <typename T>
    struct traits<Matrix<T>>
    {
        using Scalar = T;
    };

    template <typename LHS, typename RHS, BinaryOp<CommonScalar<LHS, RHS>> BinOp>
    struct traits<ElWiseOp<LHS, RHS, BinOp>>
    {
        using Scalar = CommonScalar<LHS, RHS>;
    };
}
