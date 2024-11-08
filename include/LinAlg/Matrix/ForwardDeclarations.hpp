#pragma once

namespace LinAlg
{
    template <typename Derived>
    class MatrixBase;

    template <typename T>
    class Matrix;

    template <typename LHS, typename RHS>
    class MatrixSum;

    template <typename T>
    struct traits;

    template <typename T>
    struct traits<Matrix<T>>
    {
        using Scalar = T;
    };

    template <typename LHS, typename RHS>
    struct traits<MatrixSum<LHS, RHS>>
    {
        using Scalar = std::common_type_t<typename LHS::Scalar, typename RHS::Scalar>;
    };
}
