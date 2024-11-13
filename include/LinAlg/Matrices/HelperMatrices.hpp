#include <LinAlg/Matrices/Base.hpp>

namespace LinAlg
{
    /**
     * @brief A class representing a zero matrix.
     *
     * It doesn't allocate memory, as all elements are known to be zero.
     * This is in contrast to Matrix<T>::Zero(int rows, int cols), which allocates memory and fills it with zeros.
     *
     * @tparam T
     */
    template <typename T>
    class Zero : public MatrixBase<Zero<T>>
    {
      public:
        using Scalar = T;

        Zero(int rows, int cols)
            : MatrixBase<Zero<T>>(rows, cols)
        {
        }

        T operator[](int, int) const { return 0; };
        T operator[](int) const { return 0; };

        T operator[](int, int) { return 0; };
        T operator[](int) { return 0; };
    };

    /**
     * @brief A class representing an identity matrix.
     *
     * It doesn't allocate memory. All elements are known to be zero, except for the diagonal, which is one.
     * This is in contrast to Matrix<T>::Identity(int n), which allocates memory and fills it with zeros and ones on the diagonal.
     *
     * @tparam T
     */
    template <typename T>
    class Identity : public MatrixBase<Identity<T>>
    {
      public:
        using Scalar = T;

        Identity(int n)
            : MatrixBase<Identity<T>>(n, n)
        {
        }

        T operator[](int i, int j) const { return static_cast<Scalar>(i == j); };
        T operator[](int i, int j) { return static_cast<Scalar>(i == j); };

        T operator[](int i) const { return static_cast<Scalar>(i / this->m_cols == i % this->m_cols); };
        T operator[](int i) { return static_cast<Scalar>(i / this->m_cols == i % this->m_cols); };
    };
}
