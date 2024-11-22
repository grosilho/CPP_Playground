#include <Matrices/Common/Matrix.hpp>
#include <Matrices/ET/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::ET
{
    template <typename Derived>
    using MatrixBase = LinAlg::Matrices::Common::MatrixBase<Derived>;

    template <typename T>
    using Constant = LinAlg::Matrices::Common::Constant<T>;

    template <typename T>
    using Zero = LinAlg::Matrices::Common::Zero<T>;

    template <typename T>
    using Identity = LinAlg::Matrices::Common::Identity<T>;

    template <typename T>
    class Matrix : public LinAlg::Matrices::Common::Matrix<T>
    {
      public:
        using LinAlg::Matrices::Common::Matrix<T>::Matrix;

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
