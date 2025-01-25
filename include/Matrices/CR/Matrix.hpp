#pragma once

#include <Matrices/CR/ForwardDeclarations.hpp>
#include <Matrices/Common/Matrix.hpp>

namespace LinAlg::Matrices::CR
{
    template <typename T>
    class Matrix : public LinAlg::Matrices::Common::Matrix<std::vector<T>>
    {
      public:
        using Scalar = T;
        using LinAlg::Matrices::Common::Matrix<std::vector<T>>::Matrix;

        // template <typename Func>
        // auto apply(Func&& f) const ///< Returns an expression applying the function f to all elements.
        // {
        //     return MatrixCoroutine<T>::from_fun_args(this->rows(), this->cols(), std::forward<Func>(f), *this);
        // }
    };

    using Matrixd = Matrix<double>;
    using Matrixf = Matrix<float>;
    using Matrixi = Matrix<int>;
}
