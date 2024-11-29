#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::ET
{
    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename T>
    class Matrix;

    template <typename Callable, typename... Args>
    class Expr;
}

namespace LinAlg::_implementation_details
{

    template <typename T>
    struct traits<LinAlg::Matrices::ET::Matrix<T>>
    {
        using Scalar = T;
    };

    template <typename Callable, typename... Args>
    struct traits<LinAlg::Matrices::ET::Expr<Callable, Args...>>
    {
        using Scalar = CommonScalar<Args...>;
    };
}
