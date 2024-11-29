#pragma once

#include <Matrices/Common/MatrixMultiplication.hpp>
#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename LHS, typename RHS>
        requires Concepts::BothMatrices<LHS, RHS>
    auto two_matrix_mult(LHS&& lhs, RHS&& rhs)
    {
        assert(lhs.cols() == rhs.rows() && "Matrix dimensions do not match for multiplication.");

        using T = LinAlg::CommonScalar<std::remove_cvref_t<LHS>, std::remove_cvref_t<RHS>>;
        Matrix<T> res(lhs.rows(), rhs.cols());

        for (int i = 0; i < lhs.rows(); ++i)
            for (int j = 0; j < rhs.cols(); ++j)
            {
                auto mult_view = std::views::zip(lhs.row(i), rhs.col(j)) | std::views::transform([](auto&& pair) { return std::get<0>(pair) * std::get<1>(pair); });
                res[i, j] = std::reduce(mult_view.begin(), mult_view.end(), T(0), std::plus<>());
            }

        return res;
    }
}
