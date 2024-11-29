#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>
#include <Matrices/RG/Concepts.hpp>
#include <Matrices/RG/ImplementationDetails.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename Cont>
        requires Concepts::sized_output_random_access_range<Cont>
    class MatrixCont;

    template <std::ranges::view View>
    class MatrixView;

    template <typename T>
    class Zero;

    template <typename T>
    class Constant;

    template <typename T>
    class Identity;

    template <typename T>
    class Container;
}

namespace LinAlg
{
    template <typename Cont>
    struct traits<LinAlg::Matrices::RG::MatrixCont<Cont>>
    {
        using Scalar = std::ranges::range_value_t<Cont>;
        using RGType = Cont;
    };

    template <typename View>
    struct traits<LinAlg::Matrices::RG::MatrixView<View>>
    {
        using Scalar = std::ranges::range_value_t<View>;
        using RGType = View;
    };

    template <typename T>
    struct traits<LinAlg::Matrices::RG::Zero<T>>
    {
        using Scalar = T;
        using RGType = decltype(LinAlg::Matrices::RG::_implementation_details::constant_view<T>(1, 1, 0));
    };

    template <typename T>
    struct traits<LinAlg::Matrices::RG::Constant<T>>
    {
        using Scalar = T;
        using RGType = decltype(LinAlg::Matrices::RG::_implementation_details::constant_view<T>(1, 1, 0));
    };

    template <typename T>
    struct traits<LinAlg::Matrices::RG::Identity<T>>
    {
        using Scalar = T;
        using RGType = decltype(LinAlg::Matrices::RG::_implementation_details::identity_view<T>(1));
    };
}
