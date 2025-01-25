#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::CR
{
    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename T>
    class Matrix;

    template <typename T>
    class Coroutine;
}

namespace LinAlg
{
    template <typename T>
    struct traits<LinAlg::Matrices::CR::Matrix<T>>
    {
        using Scalar = T;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::CR::Coroutine<T>>
    {
        using Scalar = T;
    };
}
