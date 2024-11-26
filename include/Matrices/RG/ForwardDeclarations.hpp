#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename T>
    using Constant = LinAlg::Matrices::Common::Constant<T>;

    template <typename T>
    using Zero = LinAlg::Matrices::Common::Zero<T>;

    template <typename T>
    using Identity = LinAlg::Matrices::Common::Identity<T>;

    template <typename T>
    class Matrix;

    namespace _implementation_details
    {
        template <typename T>
        class Container;
    }
}

namespace LinAlg::_implementation_details
{
    template <typename T>
    struct traits<LinAlg::Matrices::RG::Matrix<T>>
    {
        using Scalar = T;
    };
}
