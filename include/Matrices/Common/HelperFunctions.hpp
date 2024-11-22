#pragma once

namespace LinAlg::Matrices::Common
{
    /**
     * @brief Check if two matrices are approximately equal.
     *
     * Returns true if the matrices have the same dimensions and
     *
     * \f$ |lhs[i, j] - rhs[i, j]| \leq atol + rtol \cdot \max(|rhs[i, j]|, |rhs[i, j]|) \f$
     *
     * @tparam LHS matrix type
     * @tparam RHS matrix type
     * @param lhs matrix to compare
     * @param rhs matrix to compare
     * @param rtol relative tolerance
     * @param atol absolute tolerance
     * @return true
     * @return false
     */
    template <typename LHS, typename RHS>
    bool APPROX_EQ(const LHS& lhs, const RHS& rhs, double rtol = 1e-10, double atol = 1e-10)
    {
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
            return false;

        for (int i = 0; i < lhs.rows(); ++i)
            for (int j = 0; j < lhs.cols(); ++j)
                if (abs(lhs[i, j] - rhs[i, j]) > atol + rtol * std::max(abs(rhs[i, j]), abs(rhs[i, j])))
                    return false;

        return true;
    }

    /**
     * @brief Similar to APPROX_EQ, but we compare also the flattened view and matrix types.
     *
     * @tparam LHS matrix type
     * @tparam RHS matrix type
     * @param lhs matrix to compare
     * @param rhs matrix to compare
     * @param rtol relative tolerance
     * @param atol absolute tolerance
     * @return true
     * @return false
     */
    template <typename LHS, typename RHS>
    bool DEEP_APPROX_EQ(const LHS& lhs, const RHS& rhs, double rtol = 1e-10, double atol = 1e-10)
    {
        if constexpr (!std::is_same_v<LHS, RHS>)
            return false;

        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())
            return false;

        for (int i = 0; i < lhs.rows(); ++i)
            for (int j = 0; j < lhs.cols(); ++j)
            {
                if (abs(lhs[i, j] - rhs[i, j]) > atol + rtol * std::max(abs(rhs[i, j]), abs(rhs[i, j])))
                    return false;
                if (abs(lhs[i * lhs.cols() + j] - rhs[i * lhs.cols() + j]) > atol + rtol * std::max(abs(rhs[i * lhs.cols() + j]), abs(rhs[i * lhs.cols() + j])))
                    return false;
            }

        return true;
    }
}
