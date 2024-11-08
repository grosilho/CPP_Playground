#pragma once

#include <LinAlg/Matrix/Base.hpp>

namespace LinAlg
{
    template <typename T>
    void swap(Matrix<T>& lhs, Matrix<T>& rhs) noexcept;

    template <typename T>
    class Matrix : public MatrixBase<Matrix<T>>
    {
      public:
        using Scalar = T;
        Matrix(int rows, int cols);
        Matrix(const Matrix& other);
        Matrix(Matrix&& other) noexcept;

        template <typename OtherDerived>
        Matrix(const MatrixBase<OtherDerived>& other) noexcept;

        ~Matrix() = default;

        Matrix& operator=(Matrix other) noexcept;

        template <typename OtherDerived>
        Matrix& operator=(const Matrix<OtherDerived>& other) noexcept;

        friend void swap<T>(Matrix<T>& lhs, Matrix<T>& rhs) noexcept;

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        template <typename U>
        Matrix<T> apply(const std::function<T(U)>& f);           ///< Applies the function f to all elements and returns the result.
        Matrix<T>& apply_inplace(const std::function<T(T&)>& f); ///< Applies the function f to all elements inplace.
        Matrix<T>& zero();                                       ///< Sets all elements to zero.
        Matrix<T>& set(const T& val);                            ///< Sets all elements to val.

        static Matrix<T> Zero(int n, int m); ///< Returns the zero Matrix of size n times m.
        static Matrix<T> Identity(int n);    ///< Returns the identity Matrix of size n.

      protected:
        std::unique_ptr<T[]> m_data;
        stdex::mdspan<T, stdex::dextents<int, 2>> m_matrix;
        std::span<T, std::dynamic_extent> m_flattened;
    };
}

namespace LinAlg
{
    template <typename T>
    Matrix<T>::Matrix(int rows, int cols)
        : MatrixBase<Matrix<T>>(rows, cols)
        , m_data { rows * cols > 0 ? std::make_unique<T[]>(rows * cols) : nullptr }
    {
        if (m_data)
        {
            m_matrix = stdex::mdspan<T, stdex::dextents<int, 2>>(m_data.get(), rows, cols);
            m_flattened = std::span<T>(m_data.get(), (rows * cols));
        }
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix& other)
        : MatrixBase<Matrix<T>>(other)
        , m_data { other.m_rows * other.m_cols > 0 ? std::make_unique<T[]>(other.m_rows * other.m_cols) : nullptr }
    {
        if (m_data)
        {
            std::copy_n(other.m_data.get(), this->m_rows * this->m_cols, m_data.get());
            m_matrix = stdex::mdspan<T, stdex::dextents<int, 2>>(m_data.get(), this->m_rows, this->m_cols);
            m_flattened = std::span<T>(m_data.get(), (this->m_rows * this->m_cols));
        }
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix&& other) noexcept
        : Matrix(0, 0)
    {
        swap(*this, other);
    }

    template <typename T>
    template <typename OtherDerived>
    Matrix<T>::Matrix(const MatrixBase<OtherDerived>& other) noexcept
        : Matrix(other.rows(), other.cols())
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_flattened[i] = other[i];
    }

    template <typename T>
    template <typename OtherDerived>
    Matrix<T>& Matrix<T>::operator=(const Matrix<OtherDerived>& other) noexcept
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_flattened[i] = other[i];

        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(Matrix other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    template <typename T>
    void swap(Matrix<T>& lhs, Matrix<T>& rhs) noexcept
    {
        using std::swap;
        swap(static_cast<MatrixBase<Matrix<T>>&>(lhs), static_cast<MatrixBase<Matrix<T>>&>(rhs));
        swap(lhs.m_data, rhs.m_data);
        swap(lhs.m_matrix, rhs.m_matrix);
        swap(lhs.m_flattened, rhs.m_flattened);
    }

    template <typename T>
    Matrix<T>::Scalar& Matrix<T>::operator[](int i, int j)
    {
        return m_matrix[i, j];
    }

    template <typename T>
    Matrix<T>::Scalar Matrix<T>::operator[](int i, int j) const
    {
        return m_matrix[i, j];
    }

    template <typename T>
    Matrix<T>::Scalar& Matrix<T>::operator[](int i)
    {
        return m_flattened[i];
    }

    template <typename T>
    Matrix<T>::Scalar Matrix<T>::operator[](int i) const
    {
        return m_flattened[i];
    }

    template <typename T>
    Matrix<T>& Matrix<T>::apply_inplace(const std::function<T(T&)>& f)
    {
        std::function apply_f = [&f](T& i) { i = f(i); };
        std::ranges::for_each(m_flattened, apply_f);
        return *this;
    }

    template <typename T>
    template <typename U>
    Matrix<T> Matrix<T>::apply(const std::function<T(U)>& f)
    {
        Matrix<T> result(this->m_rows, this->m_cols);
        std::ranges::transform(m_flattened, result.m_flattened.begin(), f);
        return result;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::set(const T& val)
    {
        std::function to_val = [&val](T&) -> T { return val; };
        return apply_inplace(to_val);
    }

    template <typename T>
    Matrix<T>& Matrix<T>::zero()
    {
        std::function to_zero = [](T&) -> T { return 0; };
        return apply_inplace(to_zero);
    }

    template <typename T>
    Matrix<T> Matrix<T>::Zero(int n, int m)
    {
        return Matrix<T>(n, m).zero();
    }

    template <typename T>
    Matrix<T> Matrix<T>::Identity(int n)
    {
        Matrix<T> identity(n, n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                identity[i, j] = static_cast<Scalar>(i == j);
        return identity;
    }

}
