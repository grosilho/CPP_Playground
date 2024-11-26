#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::Common
{
    template <typename Derived>
    class MatrixBase;

    template <typename Cont>
    class Matrix;

    template <typename T>
    class Constant;

    template <typename T>
    class Zero;

    template <typename T>
    class Identity;
}

namespace LinAlg::_implementation_details
{

    template <typename T>
    struct traits;

    template <typename... Args>
    using CommonScalar = std::common_type_t<typename traits<std::remove_cvref_t<Args>>::Scalar...>;

    template <typename Cont>
    struct traits<LinAlg::Matrices::Common::Matrix<Cont>>
    {
        using Scalar = typename Cont::value_type;
        using ContType = Cont;
    };

    template <>
    struct traits<double>
    {
        using Scalar = double;
        using ContType = void;
    };

    template <>
    struct traits<float>
    {
        using Scalar = float;
        using ContType = void;
    };

    template <>
    struct traits<int>
    {
        using Scalar = int;
        using ContType = void;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Constant<T>>
    {
        using Scalar = T;
        using ContType = void;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Zero<T>>
    {
        using Scalar = T;
        using ContType = void;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Identity<T>>
    {
        using Scalar = T;
        using ContType = void;
    };

}
