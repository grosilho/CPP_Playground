#pragma once

#include <Matrices/Common/Matrix.hpp>

namespace LinAlg::Matrices::ET
{
    template <typename T>
    class Matrix : public LinAlg::Matrices::Common::Matrix<std::vector<T>>
    {
      public:
        using Scalar = T;
        using LinAlg::Matrices::Common::Matrix<std::vector<T>>::Matrix;

        template <typename Func>
        auto apply(Func&& f) const ///< Returns an expression applying the function f to all elements.
        {
            return Expr(std::forward<Func>(f), *this);
        }
    };

    using Matrixd = Matrix<double>;
    using Matrixf = Matrix<float>;
    using Matrixi = Matrix<int>;
}
