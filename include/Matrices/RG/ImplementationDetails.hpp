#pragma once

#include <Matrices/RG/Concepts.hpp>

namespace LinAlg::Matrices::RG::_implementation_details
{
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

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto zip_wrapper(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::BothMatrices<LHS, RHS>)
        {
            assert(lhs.shape() == rhs.shape());
            return std::views::zip(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        }
        else if constexpr (Concepts::MatrixType<LHS>)
            return std::views::zip(std::forward<LHS>(lhs), std::views::repeat(rhs));
        else
            return std::views::zip(std::views::repeat(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto get_shape(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::MatrixType<LHS>)
            return lhs.shape();
        else
            return rhs.shape();
    }
}
