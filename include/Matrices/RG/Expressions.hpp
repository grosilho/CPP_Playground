#pragma once

#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator+(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) + std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator-(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) - std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator*(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) * std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator/(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) / std::get<1>(pair); }));
    }

}
