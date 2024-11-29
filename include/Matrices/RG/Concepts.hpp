#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::RG::Concepts
{
    template <typename T>
    concept sized_input_range = std::ranges::sized_range<T> && std::ranges::input_range<T>;

    template <typename T>
    concept sized_output_random_access_range = std::ranges::sized_range<T> && std::ranges::output_range<T, typename T::value_type> && std::ranges::random_access_range<T>;

    template <typename T, template <typename U> class It>
    concept output_random_access_iterator = std::output_iterator<It<T>, T> && std::random_access_iterator<It<T>>;
}

namespace LinAlg::Matrices::RG
{
    template <typename Cont>
        requires Concepts::sized_output_random_access_range<Cont>
    class MatrixCont;

    template <std::ranges::view View>
    class MatrixView;
}

namespace LinAlg::Matrices::RG::Concepts
{
    template <typename T>
    using traits = LinAlg::_implementation_details::traits<T>;

    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename Mat>
    concept MatrixType = std::is_base_of_v<LinAlg::Matrices::RG::MatrixCont<typename traits<std::remove_cvref_t<Mat>>::RGType>, std::remove_cvref_t<Mat>>
        || std::is_base_of_v<LinAlg::Matrices::RG::MatrixView<typename traits<std::remove_cvref_t<Mat>>::RGType>, std::remove_cvref_t<Mat>>;
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
}
