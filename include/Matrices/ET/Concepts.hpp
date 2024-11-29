#pragma once

#include <Matrices/ET/ForwardDeclarations.hpp>
#include <stdafx.hpp>

namespace LinAlg::Matrices::ET::Concepts
{

}

namespace LinAlg::Matrices::ET
{
    template <typename T>
    class Matrix;
}

namespace LinAlg::Matrices::ET::Concepts
{
    template <typename T>
    concept MatrixType
        = std::is_base_of_v<MatrixBase<std::remove_cvref_t<T>>, std::remove_cvref_t<T>> || std::is_same_v<Matrix<typename LinAlg::traits<std::remove_cvref_t<T>>::Scalar>, std::remove_cvref_t<T>>;
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
