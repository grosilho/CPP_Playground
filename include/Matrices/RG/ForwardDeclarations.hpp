#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>
#include <Matrices/Common/HelperMatrices.hpp>

namespace LinAlg::Matrices::RG
{
    namespace _implementation_details
    {
        template <typename T>
        concept sized_input_range = std::ranges::sized_range<T> && std::ranges::input_range<T>;
        template <typename T>
        concept sized_output_random_access_range = std::ranges::sized_range<T> && std::ranges::output_range<T, typename T::value_type> && std::ranges::random_access_range<T>;

        template <typename T>
        class Container;

        template <typename Derived>
        class RangeWrapper
        {
          private:
            Derived& derived() { return static_cast<Derived&>(*this); }
            const Derived& derived() const { return static_cast<const Derived&>(*this); }

          public:
            auto begin() { return derived().data().begin(); }
            auto end() { return derived().data().end(); }
            auto begin() const { return derived().data().cbegin(); }
            auto end() const { return derived().data().cend(); }
            auto cbegin() const { return derived().data().cbegin(); }
            auto cend() const { return derived().data().cend(); }

            auto row(int i) const { return derived().data() | std::views::drop(i * derived().cols()) | std::views::take(derived().cols()); }
            auto col(int j) const { return derived().data() | std::views::drop(j) | std::views::stride(derived().cols()) | std::views::take(derived().rows()); }
        };

        template <typename T>
        auto constant_view(int rows, int cols, const T& value)
        {
            return std::views::repeat(T(value)) | std::views::take(rows * cols);
        }

        template <typename T>
        auto identity_view(int n)
        {
            return std::views::iota(0, n * n) | std::views::transform([n](int i) { return static_cast<T>(i == (i / n) * (n + 1)); });
        }
    }

    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename Cont>
        requires _implementation_details::sized_output_random_access_range<Cont>
    class MatrixCont;

    template <std::ranges::view View>
    class MatrixView;

    template <typename T>
    class Zero;

    template <typename T>
    class Constant;

    template <typename T>
    class Identity;

}

namespace LinAlg::_implementation_details
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
