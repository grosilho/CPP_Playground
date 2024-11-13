#pragma once

namespace LinAlg
{
    template <typename Derived>
    class MatrixBase;

    template <typename T>
    class Matrix;

    template <typename Callable, typename... Args>
    class Expr;

    template <typename T>
    struct traits;

    template <typename... Args>
    using CommonScalar = std::common_type_t<typename traits<Args>::Scalar...>;

    template <typename T>
    struct traits<Matrix<T>>
    {
        using Scalar = T;
        using is_leaf = std::true_type;
    };

    template <>
    struct traits<double>
    {
        using Scalar = double;
        using is_leaf = std::true_type;
    };

    template <typename Callable, typename... Args>
    struct traits<Expr<Callable, Args...>>
    {
        using Scalar = CommonScalar<Args...>;
        using is_leaf = std::false_type;
    };
}
