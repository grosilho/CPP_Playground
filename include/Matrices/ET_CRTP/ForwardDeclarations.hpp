#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::ET_CRTP
{
    template <typename Derived>
    class MatrixBase;

    template <typename T>
    class Matrix;

    template <typename T>
    class Constant;

    template <typename T>
    class Zero;

    template <typename T>
    class Identity;

    template <typename Callable, typename... Args>
    class Expr;

    namespace _implementation_details
    {

        template <typename T>
        struct traits;

        template <typename... Args>
        using CommonScalar = std::common_type_t<typename traits<std::remove_cvref_t<Args>>::Scalar...>;

        template <typename T>
        struct traits<Matrix<T>>
        {
            using Scalar = T;
        };

        template <>
        struct traits<double>
        {
            using Scalar = double;
        };

        template <typename T>
        struct traits<Constant<T>>
        {
            using Scalar = T;
        };

        template <typename T>
        struct traits<Zero<T>>
        {
            using Scalar = T;
        };

        template <typename T>
        struct traits<Identity<T>>
        {
            using Scalar = T;
        };

        template <typename Callable, typename... Args>
        struct traits<Expr<Callable, Args...>>
        {
            using Scalar = CommonScalar<Args...>;
        };
    }
}
