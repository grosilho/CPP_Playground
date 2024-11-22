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
        using Scalar = _implementation_details::traits<Derived>::Scalar;

        MatrixBase(int rows, int cols);
        MatrixBase(const MatrixBase& other);
        MatrixBase(MatrixBase&& other) noexcept;
        ~MatrixBase() = default;

        MatrixBase& operator=(MatrixBase other) noexcept;
        friend void swap<Derived>(MatrixBase& lhs, MatrixBase& rhs) noexcept;

        void reinit(int rows, int cols);
        void init_from_list(std::initializer_list<std::initializer_list<Scalar>> list);

        std::pair<int, int> shape() const; ///< Returns the number of rows and columns.
        int cols() const;                  ///< Returns the number of columns.
        int rows() const;                  ///< Returns the number of rows.
        int size() const;                  ///< Returns the number of elements.

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        template <typename Func>
        Derived& apply_inplace(Func&& f); ///< Applies the function f to all elements inplace.
        Derived& zero();                  ///< Sets all elements to zero.
        Derived& set(const Scalar& val);  ///< Sets all elements to val.

        static Derived Constant(int rows, int cols, const Scalar& value); ///< Returns a Matrix with given dimensions and constant coefficients.
        static Derived Zero(int rows, int cols);                          ///< Returns the zero Matrix with given dimensions.
        static Derived Identity(int n);                                   ///< Returns the identity Matrix of size n.
        static Derived randn(int rows, int cols, Scalar mean = 0, Scalar stddev = 1, Scalar min_abs_value = 0, std::optional<int> seed = std::nullopt);

        const Derived& eval() const; ///< Dummy method returning a reference to *this. Needed in derived expressions but not here.

      protected:
        const Derived& derived() const;
        Derived& derived();
        template <typename T = Scalar>
        std::span<T, std::dynamic_extent>& data();

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
    void MatrixBase<Derived>::init_from_list(std::initializer_list<std::initializer_list<Scalar>> list)
    {
        int i = 0;
        for (const auto& row : list)
        {
            int j = 0;
            for (const auto& elem : row)
            {
                derived()[i, j] = elem;
                ++j;
            }
            ++i;
        }
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
    template <typename Func>
    Derived& MatrixBase<Derived>::apply_inplace(Func&& f)
    {
        std::function apply_f = [&f](Scalar& i) { i = f(i); };
        std::ranges::for_each(data(), apply_f);
        return derived();
    }

    template <typename Derived>
    Derived& MatrixBase<Derived>::zero()
    {
        return apply_inplace([](Scalar&) -> Scalar { return 0; });
    }

    template <typename Derived>
    Derived& MatrixBase<Derived>::set(const Scalar& val)
    {
        return apply_inplace([&val](Scalar&) -> Scalar { return val; });
    }

    template <typename Derived>
    Derived MatrixBase<Derived>::Constant(int rows, int cols, const Scalar& value)
    {
        return Derived(LinAlg::Matrices::Common::Constant<Scalar>(rows, cols, value));
    }

    template <typename Derived>
    Derived MatrixBase<Derived>::Zero(int rows, int cols)
    {
        return Derived(LinAlg::Matrices::Common::Zero<Scalar>(rows, cols));
    }

    template <typename Derived>
    Derived MatrixBase<Derived>::Identity(int n)
    {
        return Derived(LinAlg::Matrices::Common::Identity<Scalar>(n));
    }

    /**
     * @brief Returns a Matrix with coefficients sampled from a normal distribution.
     *
     * The min_abs_value parameter is used to ensure that the absolute value of the coefficients is greater or equal to this value.
     * Used to avoid division by zero in some element wise operations.
     *
     * @tparam T type
     * @param rows number of rows
     * @param cols number of columns
     * @param mean mean
     * @param stddev standard deviation
     * @param min_abs_value minimum allowed absolute value
     * @param seed random seed
     * @return Matrix<T>
     */
    template <typename Derived>
    Derived MatrixBase<Derived>::randn(int rows, int cols, Scalar mean, Scalar stddev, Scalar min_abs_value, std::optional<int> seed)
    {
        std::mt19937 gen(seed.value_or(std::random_device()()));
        std::normal_distribution<double> dist(mean, stddev);
        Derived result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
            {
                result[i, j] = static_cast<Scalar>(dist(gen));
                while (abs(result[i, j]) < min_abs_value)
                    result[i, j] = static_cast<Scalar>(dist(gen));
            }
        return result;
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
    template <typename T>
    std::span<T, std::dynamic_extent>& MatrixBase<Derived>::data()
    {
        return derived().data();
    }

} // namespace LinAlg
