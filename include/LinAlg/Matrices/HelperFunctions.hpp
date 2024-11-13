#pragma once

namespace LinAlg
{
    template <typename LHS, typename RHS>
    bool APPROX_EQ(const LHS& lhs, const RHS& rhs, double rtol = 1e-10, double atol = 1e-10)
    {
        for (int i = 0; i < lhs.rows(); ++i)
            for (int j = 0; j < lhs.cols(); ++j)
                if (abs(lhs[i, j] - rhs[i, j]) > atol + rtol * std::max(abs(rhs[i, j]), abs(rhs[i, j])))
                    return false;

        return true;
    }
}
