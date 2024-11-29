#pragma once

#include <Matrices/Common/ForwardDeclarations.hpp>
#include <stdafx.hpp>

namespace LinAlg::Matrices::Common
{
    /**
     * @brief A friend function to swap two MatrixBase objects.
     *
     * @tparam Derived
     * @param lhs
     * @param rhs
     */

    template <typename Derived>
    void swap(MatrixBase<Derived>& lhs, MatrixBase<Derived>& rhs) noexcept;

    template <typename Derived>
    std::ostream& operator<<(std::ostream& os, const MatrixBase<Derived>& mat);

    /**
     * @brief A MatrixBase class for all matrix types.
     *
     * It uses CRTP, so Derived corresponds to the derived class. This is used to access the derived class in the base class at compile time.
     *
     * @tparam Derived
     */
    template <typename Derived>
    class MatrixBase
    {
      public:
        using Scalar = traits<Derived>::Scalar;

        MatrixBase(int rows, int cols);
        MatrixBase(const MatrixBase& other);
        MatrixBase(MatrixBase&& other) noexcept;
        ~MatrixBase() = default;

        MatrixBase& operator=(MatrixBase other) noexcept;
        friend void swap<Derived>(MatrixBase& lhs, MatrixBase& rhs) noexcept;

        void reinit(int rows, int cols);

        std::pair<int, int> shape() const; ///< Returns the number of rows and columns.
        int cols() const;                  ///< Returns the number of columns.
        int rows() const;                  ///< Returns the number of rows.
        int size() const;                  ///< Returns the number of elements.

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        const Derived& eval() const; ///< Dummy method returning a reference to *this. Needed in derived expressions but not here.

        friend std::ostream& operator<< <Derived>(std::ostream& os, const MatrixBase& mat);

      protected:
        const Derived& derived() const;
        Derived& derived();

        int m_rows;
        int m_cols;
    };

} // namespace LinAlg

/*
    Implementation
    -----------------------------------------------------------------------------------------
*/
namespace LinAlg::Matrices::Common
{

    /**
     * @brief Construct a new MatrixBase< Derived> object
     *
     * Memory allocation is done in derived class, if needed.
     *
     * @tparam Derived
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
    MatrixBase<Derived>& MatrixBase<Derived>::operator=(MatrixBase other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    template <typename Derived>
    void swap(MatrixBase<Derived>& lhs, MatrixBase<Derived>& rhs) noexcept
    {
        using std::swap;
        swap(lhs.m_rows, rhs.m_rows);
        swap(lhs.m_cols, rhs.m_cols);
    }

    /**
     * @brief Reinit the object given new dimensions.
     *
     * Needed for when the dimensions are known only after construction.
     *
     * @tparam Derived
     * @param rows
     * @param cols
     */
    template <typename Derived>
    void MatrixBase<Derived>::reinit(int rows, int cols)
    {
        m_rows = rows;
        m_cols = cols;
    }

    template <typename Derived>
    std::pair<int, int> MatrixBase<Derived>::shape() const
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
    int MatrixBase<Derived>::size() const
    {
        return m_rows * m_cols;
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar& MatrixBase<Derived>::operator[](int i, int j)
    {
        return derived()[i, j];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar MatrixBase<Derived>::operator[](int i, int j) const
    {
        return derived()[i, j];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar& MatrixBase<Derived>::operator[](int i)
    {
        return derived()[i];
    }

    template <typename Derived>
    MatrixBase<Derived>::Scalar MatrixBase<Derived>::operator[](int i) const
    {
        return derived()[i];
    }

    template <typename Derived>
    const Derived& MatrixBase<Derived>::eval() const
    {
        return *this;
    }

    template <typename Derived>
    const Derived& MatrixBase<Derived>::derived() const
    {
        return static_cast<const Derived&>(*this);
    }

    template <typename Derived>
    Derived& MatrixBase<Derived>::derived()
    {
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    std::ostream& operator<<(std::ostream& os, const MatrixBase<Derived>& mat)
    {
        for (int i = 0; i < mat.rows(); ++i)
        {
            for (int j = 0; j < mat.cols(); ++j)
                os << mat[i, j] << ' ';
            os << '\n';
        }
        return os;
    }

} // namespace LinAlg
