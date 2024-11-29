#pragma once

#include <Matrices/Common/MatrixMultiplication.hpp>
#include <Matrices/ET/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::ET
{
    template <typename LHS, typename RHS>
    auto two_matrix_mult(LHS&& lhs, RHS&& rhs)
    {
        assert(lhs.cols() == rhs.rows() && "Matrix dimensions do not match for multiplication.");

        using T = LinAlg::CommonScalar<std::remove_cvref_t<LHS>, std::remove_cvref_t<RHS>>;
        Matrix<T> res(lhs.rows(), rhs.cols());

        for (int i = 0; i < lhs.rows(); ++i)
            for (int j = 0; j < rhs.cols(); ++j)
            {

                res[i, j] = lhs[i, 0] * rhs[0, j];
                for (int k = 1; k < lhs.cols(); ++k)
                    res[i, j] += lhs[i, k] * rhs[k, j];
            }

        return res;
    }
}
