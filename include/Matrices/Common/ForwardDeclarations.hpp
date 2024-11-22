#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::Common
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
}

namespace LinAlg::_implementation_details
{

    template <typename T>
    struct traits;

    template <typename... Args>
    using CommonScalar = std::common_type_t<typename traits<std::remove_cvref_t<Args>>::Scalar...>;

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Matrix<T>>
    {
        using Scalar = T;
    };

    template <>
    struct traits<double>
    {
        using Scalar = double;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Constant<T>>
    {
        using Scalar = T;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Zero<T>>
    {
        using Scalar = T;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::Common::Identity<T>>
    {
        using Scalar = T;
    };

}
