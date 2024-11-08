#pragma once
#include <LinAlg/Matrix/ForwardDeclarations.hpp>
#include <stdafx.hpp>

namespace LinAlg
{
    template <typename Derived>
    void swap(MatrixBase<Derived>& lhs, MatrixBase<Derived>& rhs) noexcept;

    template <typename Derived>
    class MatrixBase
    {
      public:
        using Scalar = traits<Derived>::Scalar;

        MatrixBase(int rows, int cols);
        MatrixBase(const MatrixBase& other);
        MatrixBase(MatrixBase&& other) noexcept;
        ~MatrixBase() = default;

        friend void swap<Derived>(MatrixBase& lhs, MatrixBase& rhs) noexcept;

        MatrixBase& operator=(MatrixBase other) noexcept;

        std::pair<int, int> size() const; ///< Returns the number of rows and columns.
        int cols() const;                 ///< Returns the number of columns.
        int rows() const;                 ///< Returns the number of rows.

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        const Derived& derived() const;

      protected:
        int m_rows;
        int m_cols;
    };

} // namespace LinAlg

namespace LinAlg
{
    /**
     * @brief Construct a new MatrixBase given the number of rows and columns.
     *
     * Allocates memory but does not initialize it.
     *
     * @param rows
     * @param cols
     */
    template <typename Derived>
    MatrixBase<Derived>::MatrixBase(int rows, int cols)
        : m_rows { rows }
        , m_cols { cols }
    {
    }

    template <typename Derived>
    MatrixBase<Derived>::MatrixBase(const MatrixBase& other)
        : m_rows { other.m_rows }
        , m_cols { other.m_cols }
    {
    }

    template <typename Derived>
    MatrixBase<Derived>::MatrixBase(MatrixBase&& other) noexcept
        : MatrixBase(0, 0)
    {
        swap(*this, other);
    }

    template <typename Derived>
    void swap(MatrixBase<Derived>& lhs, MatrixBase<Derived>& rhs) noexcept
    {
        using std::swap;
        swap(lhs.m_rows, rhs.m_rows);
        swap(lhs.m_cols, rhs.m_cols);
    }

    template <typename Derived>
    MatrixBase<Derived>& MatrixBase<Derived>::operator=(MatrixBase other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    template <typename Derived>
    std::pair<int, int> MatrixBase<Derived>::size() const
    {
        return std::make_pair(m_rows, m_cols);
    }

    template <typename Derived>
    int MatrixBase<Derived>::cols() const
    {
        return m_cols;
    }

    template <typename Derived>
    int MatrixBase<Derived>::rows() const
    {
        return m_rows;
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar& MatrixBase<Derived>::operator[](int i, int j)
    {
        return static_cast<Derived&>(*this)[i, j];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar MatrixBase<Derived>::operator[](int i, int j) const
    {
        return static_cast<const Derived&>(*this)[i, j];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar& MatrixBase<Derived>::operator[](int i)
    {
        return static_cast<Derived&>(*this)[i];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar MatrixBase<Derived>::operator[](int i) const
    {
        return static_cast<const Derived&>(*this)[i];
    }

    template <typename Derived>
    const Derived& MatrixBase<Derived>::derived() const
    {
        return static_cast<const Derived&>(*this);
    }

} // namespace LinAlg
