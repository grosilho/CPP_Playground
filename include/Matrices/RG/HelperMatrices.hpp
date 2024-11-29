#pragma once
#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename T>
    using constant_view_type = decltype(_implementation_details::constant_view<T>(1, 1, 0));
    template <typename T>
    using identity_view_type = decltype(_implementation_details::identity_view<T>(1));

    template <typename T>
    class Zero : public MatrixView<constant_view_type<T>>
    {
      public:
        using Scalar = T;
        using RGType = constant_view_type<T>;

        Zero(int rows, int cols)
            : MatrixView<constant_view_type<T>>(rows, cols, _implementation_details::constant_view<T>(rows, cols, 0))
        {
        }
    };

    template <typename T>
    class Constant : public MatrixView<constant_view_type<T>>
    {
      public:
        using Scalar = T;
        using RGType = constant_view_type<T>;

        Constant(int rows, int cols, const T& value)
            : MatrixView<constant_view_type<T>>(rows, cols, _implementation_details::constant_view<T>(rows, cols, value))
        {
        }
    };

    template <typename T>
    class Identity : public MatrixView<identity_view_type<T>>
    {
      public:
        using Scalar = T;
        using RGType = identity_view_type<T>;

        Identity(int n)
            : MatrixView<identity_view_type<T>>(n, n, _implementation_details::identity_view<T>(n))
        {
        }
    };
}
