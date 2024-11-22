#pragma once

#include <Matrices/ET/Base.hpp>
#include <Matrices/ET/HelperMatrices.hpp>

namespace LinAlg::Matrices::ET
{
    /**
     * @brief A friend function to swap two Matrix objects.
     *
     * @tparam T
     * @param lhs
     * @param rhs
     */
    template <typename T>
    void swap(Matrix<T>& lhs, Matrix<T>& rhs) noexcept;

    /**
     * @brief The main Matrix class.
     *
     * Represents a dense matrix with elements of type T.
     *
     * @tparam T
     */
    template <typename T>
    class Matrix : public MatrixBase<Matrix<T>>
    {
      public:
        using Scalar = T;
        friend class MatrixBase<Matrix<T>>;

        Matrix(int rows = 0, int cols = 0);                           ///< Construct a new Matrix object with the given dimensions.
        Matrix(const Matrix& other);                                  ///< Copy constructor.
        Matrix(Matrix&& other) noexcept;                              ///< Move constructor.
        Matrix(std::initializer_list<std::initializer_list<T>> list); ///< Construct a new Matrix object from embedded initializer lists.
        ~Matrix() = default;

        Matrix& operator=(Matrix other) noexcept; ///< Copy assignment. Uses copy and swap idiom.
        friend void swap<T>(Matrix<T>& lhs, Matrix<T>& rhs) noexcept;

        template <typename OtherDerived>
        Matrix(const MatrixBase<OtherDerived>& other) noexcept; ///< Construct a new Matrix object from a MatrixBase object.
        template <typename OtherDerived>
        Matrix& operator=(const MatrixBase<OtherDerived>& other) noexcept; ///< Copy assignment from a MatrixBase object. It forces expressions to be evaluated.

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        template <typename Func>
        auto apply(Func&& f) const; ///< Returns an expression applying the function f to all elements.

      protected:
        std::span<Scalar, std::dynamic_extent>& data();

        std::unique_ptr<T[]> m_data;
        stdex::mdspan<T, stdex::dextents<int, 2>> m_matrix;
        std::span<T, std::dynamic_extent> m_flattened;
    };
}

/*
    Implementation
    -----------------------------------------------------------------------------------------
*/

namespace LinAlg::Matrices::ET
{
    template <typename T>
    Matrix<T>::Matrix(int rows, int cols)
        : MatrixBase<Matrix<T>>(rows, cols)
        , m_data { rows * cols > 0 ? std::make_unique<T[]>(rows * cols) : nullptr }
        , m_matrix { m_data.get(), rows, cols }
        , m_flattened { m_data.get(), (static_cast<std::size_t>(rows * cols)) }
    {
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
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
        : Matrix(list.size(), list.begin()->size())
    {
        this->init_from_list(list);
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
    template <typename OtherDerived>
    Matrix<T>::Matrix(const MatrixBase<OtherDerived>& other) noexcept
        : Matrix(other.rows(), other.cols())
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_flattened[i] = other[i];
    }

    template <typename T>
    template <typename OtherDerived>
    Matrix<T>& Matrix<T>::operator=(const MatrixBase<OtherDerived>& other) noexcept
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_flattened[i] = other[i];

        return *this;
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
    template <typename Func>
    auto Matrix<T>::apply(Func&& f) const
    {
        return Expr(std::forward<Func>(f), *this);
    }

    template <typename T>
    std::span<T, std::dynamic_extent>& Matrix<T>::data()
    {
        return m_flattened;
    }
}
