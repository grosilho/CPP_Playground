#pragma once
#include <Matrices/RG/ForwardDeclarations.hpp>
#include <Matrices/RG/Matrix.hpp>
#include <Matrices/RG/MatrixView.hpp>

namespace LinAlg::Matrices::RG
{
    namespace _implementation_details
    {
        template <typename T>
        using traits = LinAlg::_implementation_details::traits<T>;

        template <typename Derived>
        using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

        template <typename Mat>
        concept MatrixType = std::is_base_of_v<MatrixCont<typename traits<std::remove_cvref_t<Mat>>::RGType>, std::remove_cvref_t<Mat>>
            || std::is_base_of_v<MatrixView<typename traits<std::remove_cvref_t<Mat>>::RGType>, std::remove_cvref_t<Mat>>;
        template <typename T>
        concept ScalarType = std::is_integral_v<std::remove_cvref_t<T>> || std::is_floating_point_v<std::remove_cvref_t<T>>;
        template <typename T>
        concept AllowedType = MatrixType<T> || ScalarType<T>;
        template <typename T, typename U>
        concept BothScalars = ScalarType<T> && ScalarType<U>;
        template <typename T, typename U>
        concept BothMatrices = MatrixType<T> && MatrixType<U>;
        template <typename LHS, typename RHS>
        concept AcceptedTypes = AllowedType<LHS> && AllowedType<RHS> && !BothScalars<LHS, RHS>;

        template <typename LHS, typename RHS>
            requires _implementation_details::AcceptedTypes<LHS, RHS>
        auto zip_wrapper(LHS&& lhs, RHS&& rhs)
        {
            if constexpr (_implementation_details::BothMatrices<LHS, RHS>)
            {
                assert(lhs.shape() == rhs.shape());
                return std::views::zip(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
            }
            else if constexpr (_implementation_details::MatrixType<LHS>)
                return std::views::zip(std::forward<LHS>(lhs), std::views::repeat(rhs));
            else
                return std::views::zip(std::views::repeat(lhs), std::forward<RHS>(rhs));
        }

        template <typename LHS, typename RHS>
            requires _implementation_details::AcceptedTypes<LHS, RHS>
        auto get_shape(LHS&& lhs, RHS&& rhs)
        {
            if constexpr (_implementation_details::MatrixType<LHS>)
                return lhs.shape();
            else
                return rhs.shape();
        }
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator+(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) + std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator-(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) - std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator*(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) * std::get<1>(pair); }));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator/(LHS&& lhs, RHS&& rhs)
    {
        auto shape = get_shape(std::forward<LHS>(lhs), std::forward<RHS>(rhs));
        return MatrixView(
            shape.first, shape.second, zip_wrapper(std::forward<LHS>(lhs), std::forward<RHS>(rhs)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) / std::get<1>(pair); }));
    }

}
