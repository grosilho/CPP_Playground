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
        Matrix(int rows = 0, int cols = 0);                           ///< Construct a new Matrix object with the given dimensions.
        Matrix(const Matrix& other);                                  ///< Copy constructor.
        Matrix(Matrix&& other) noexcept;                              ///< Move constructor.
        Matrix(std::initializer_list<std::initializer_list<T>> list); ///< Construct a new Matrix object from embedded initializer lists.

        template <typename OtherDerived>
        Matrix(const MatrixBase<OtherDerived>& other) noexcept; ///< Construct a new Matrix object from a MatrixBase object.

        ~Matrix() = default;

        Matrix& operator=(Matrix other) noexcept; ///< Copy assignment. Uses copy and swap idiom.

        template <typename OtherDerived>
        Matrix& operator=(const Matrix<OtherDerived>& other) noexcept; ///< Copy assignment from a MatrixBase object. It forces expressions to be evaluated.

        friend void swap<T>(Matrix<T>& lhs, Matrix<T>& rhs) noexcept;

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        template <typename Func>
        Matrix<T> apply(Func&& f) const; ///< Applies the function f to all elements and returns the result in a new Matrix.
        template <typename Func>
        Matrix<T>& apply_inplace(Func&& f); ///< Applies the function f to all elements inplace.
        Matrix<T>& zero();                  ///< Sets all elements to zero.
        Matrix<T>& set(const T& val);       ///< Sets all elements to val.

        const Matrix<T>& eval() const; ///< Dummy method returning a reference to *this. Needed for expressions but not here.

        static Matrix<T> Constant(int rows, int cols, const T& value); ///< Returns a Matrix with given dimensions and constant coefficients.
        static Matrix<T> Zero(int rows, int cols);                     ///< Returns the zero Matrix with given dimensions.
        static Matrix<T> Identity(int n);                              ///< Returns the identity Matrix of size n.
        static Matrix<T> randn(int rows, int cols, T mean = 0, T stddev = 1, T min_abs_value = 0, std::optional<int> seed = std::nullopt);

      protected:
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
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
        : Matrix(list.size(), list.begin()->size())
    {
        int i = 0;
        for (const auto& row : list)
        {
            int j = 0;
            for (const auto& elem : row)
            {
                m_matrix[i, j] = elem;
                ++j;
            }
            ++i;
        }
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
    template <typename Func>
    Matrix<T>& Matrix<T>::apply_inplace(Func&& f)
    {
        std::function apply_f = [&f](T& i) { i = f(i); };
        std::ranges::for_each(m_flattened, apply_f);
        return *this;
    }

    template <typename T>
    template <typename Func>
    Matrix<T> Matrix<T>::apply(Func&& f) const
    {
        Matrix<T> result(this->m_rows, this->m_cols);
        std::ranges::transform(m_flattened, result.m_flattened.begin(), f);

        return result;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::set(const T& val)
    {
        return apply_inplace([&val](T&) -> T { return val; });
    }

    template <typename T>
    const Matrix<T>& Matrix<T>::eval() const
    {
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::zero()
    {
        return apply_inplace([](T&) -> T { return 0; });
    }

    template <typename T>
    Matrix<T> Matrix<T>::Constant(int rows, int cols, const T& value)
    {
        return Matrix<T>(LinAlg::Matrices::ET::Constant<T>(rows, cols, value));
    }

    template <typename T>
    Matrix<T> Matrix<T>::Zero(int rows, int cols)
    {
        return Matrix<T>(LinAlg::Matrices::ET::Zero<T>(rows, cols));
    }

    template <typename T>
    Matrix<T> Matrix<T>::Identity(int n)
    {
        return Matrix<T>(LinAlg::Matrices::ET::Identity<T>(n));
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
    template <typename T>
    Matrix<T> Matrix<T>::randn(int rows, int cols, T mean, T stddev, T min_abs_value, std::optional<int> seed)
    {
        std::mt19937 gen(seed.value_or(std::random_device()()));
        std::normal_distribution<double> dist(mean, stddev);
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
            {
                result[i, j] = static_cast<T>(dist(gen));
                while (abs(result[i, j]) < min_abs_value)
                    result[i, j] = static_cast<T>(dist(gen));
            }
        return result;
    }

}
