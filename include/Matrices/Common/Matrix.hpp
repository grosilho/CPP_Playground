#pragma once

#include <Matrices/Common/Base.hpp>
#include <Matrices/Common/HelperMatrices.hpp>

namespace LinAlg::Matrices::Common
{
    template <typename Cont>
    void swap(Matrix<Cont>& lhs, Matrix<Cont>& rhs) noexcept;

    template <typename Cont>
    class Matrix : public LinAlg::Matrices::Common::MatrixBase<Matrix<Cont>>
    {
      public:
        using Scalar = typename Cont::value_type;
        friend class LinAlg::Matrices::Common::MatrixBase<Matrix<Cont>>;

        Matrix(int rows = 0, int cols = 0);
        Matrix(const Matrix& other);                                       ///< Copy constructor.
        Matrix(Matrix&& other) noexcept;                                   ///< Move constructor.
        Matrix(std::initializer_list<std::initializer_list<Scalar>> list); ///< Construct a new Matrix object from embedded initializer lists.
        ~Matrix() = default;

        Matrix& operator=(Matrix other) noexcept; ///< Copy assignment. Uses copy and swap idiom.
        friend void swap<Cont>(Matrix<Cont>& lhs, Matrix<Cont>& rhs) noexcept;

        template <typename OtherDerived>
        Matrix(const MatrixBase<OtherDerived>& other) noexcept; ///< Construct a new Matrix object from a MatrixBase object.
        template <typename OtherDerived>
        Matrix& operator=(const MatrixBase<OtherDerived>& other) noexcept; ///< Copy assignment from a MatrixBase object. It forces expressions to be evaluated.

        void init_from_list(std::initializer_list<std::initializer_list<Scalar>> list);

        Scalar& operator[](int i, int j);      ///< Access the element at row i and column j.
        Scalar operator[](int i, int j) const; ///< Access the element at row i and column j.
        Scalar& operator[](int i);             ///< Access the element i in the flattened matrix.
        Scalar operator[](int i) const;        ///< Access the element i in the flattened matrix.

        Cont& data() { return this->m_data; }
        const Cont& data() const { return this->m_data; }

        template <typename Func>
        Matrix<Cont>& apply_inplace(Func&& f); ///< Applies the function f to all elements inplace.
        Matrix<Cont>& zero();                  ///< Sets all elements to zero.
        Matrix<Cont>& set(const Scalar& val);  ///< Sets all elements to val.

        static Matrix<Cont> Constant(int rows, int cols, const Scalar& value); ///< Returns a Matrix with given dimensions and constant coefficients.
        static Matrix<Cont> Zero(int rows, int cols);                          ///< Returns the zero Matrix with given dimensions.
        static Matrix<Cont> Identity(int n);                                   ///< Returns the identity Matrix of size n.
        static Matrix<Cont> randn(int rows, int cols, Scalar mean = 0, Scalar stddev = 1, Scalar min_abs_value = 0, std::optional<int> seed = std::nullopt);

      protected:
        Cont m_data {};
    };

}

namespace LinAlg::Matrices::Common
{
    template <typename Cont>
    Matrix<Cont>::Matrix(int rows, int cols)
        : LinAlg::Matrices::Common::MatrixBase<Matrix<Cont>>(rows, cols)
        , m_data(rows * cols)
    {
    }

    template <typename Cont>
    Matrix<Cont>::Matrix(const Matrix& other)
        : LinAlg::Matrices::Common::MatrixBase<Matrix<Cont>>(other)
        , m_data(other.m_data)
    {
    }

    template <typename Cont>
    Matrix<Cont>::Matrix(Matrix&& other) noexcept
        : Matrix(0, 0)
    {
        swap(*this, other);
    }

    template <typename Cont>
    Matrix<Cont>::Matrix(std::initializer_list<std::initializer_list<Scalar>> list)
        : Matrix(list.size(), list.begin()->size())
    {
        this->init_from_list(list);
    }

    template <typename Cont>
    Matrix<Cont>& Matrix<Cont>::operator=(Matrix other) noexcept
    {
        swap(*this, other);
        return *this;
    }

    template <typename Cont>
    void swap(Matrix<Cont>& lhs, Matrix<Cont>& rhs) noexcept
    {
        using std::swap;
        swap(static_cast<MatrixBase<Matrix<Cont>>&>(lhs), static_cast<MatrixBase<Matrix<Cont>>&>(rhs));
        swap(lhs.m_data, rhs.m_data);
    }

    template <typename Cont>
    template <typename OtherDerived>
    Matrix<Cont>::Matrix(const MatrixBase<OtherDerived>& other) noexcept
        : Matrix(other.rows(), other.cols())
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_data[i] = other[i];
    }

    template <typename Cont>
    template <typename OtherDerived>
    Matrix<Cont>& Matrix<Cont>::operator=(const MatrixBase<OtherDerived>& other) noexcept
    {
        for (int i = 0; i < (this->m_rows * this->m_cols); ++i)
            m_data[i] = other[i];

        return *this;
    }

    template <typename Cont>
    void Matrix<Cont>::init_from_list(std::initializer_list<std::initializer_list<Scalar>> list)
    {
        int i = 0;
        for (const auto& row : list)
        {
            int j = 0;
            for (const auto& elem : row)
            {
                (*this)[i, j] = elem;
                ++j;
            }
            ++i;
        }
    }

    template <typename Cont>
    typename Matrix<Cont>::Scalar& Matrix<Cont>::operator[](int i, int j)
    {
        return m_data[i * this->m_cols + j];
    }

    template <typename Cont>
    typename Matrix<Cont>::Scalar Matrix<Cont>::operator[](int i, int j) const
    {
        return m_data[i * this->m_cols + j];
    }

    template <typename Cont>
    typename Matrix<Cont>::Scalar& Matrix<Cont>::operator[](int i)
    {
        return m_data[i];
    }

    template <typename Cont>
    typename Matrix<Cont>::Scalar Matrix<Cont>::operator[](int i) const
    {
        return m_data[i];
    }

    template <typename Cont>
    template <typename Func>
    Matrix<Cont>& Matrix<Cont>::apply_inplace(Func&& f)
    {
        std::function apply_f = [&f](Scalar& i) { i = f(i); };
        std::for_each(this->m_data.begin(), this->m_data.end(), apply_f);
        return *this;
    }

    template <typename Cont>
    Matrix<Cont>& Matrix<Cont>::zero()
    {
        return apply_inplace([](Scalar&) -> Scalar { return 0; });
    }

    template <typename Cont>
    Matrix<Cont>& Matrix<Cont>::set(const Scalar& val)
    {
        return apply_inplace([&val](Scalar&) -> Scalar { return val; });
    }

    template <typename Cont>
    Matrix<Cont> Matrix<Cont>::Constant(int rows, int cols, const Scalar& value)
    {
        return LinAlg::Matrices::Common::Constant<Scalar>(rows, cols, value);
    }

    template <typename Cont>
    Matrix<Cont> Matrix<Cont>::Zero(int rows, int cols)
    {
        return LinAlg::Matrices::Common::Zero<Scalar>(rows, cols);
    }

    template <typename Cont>
    Matrix<Cont> Matrix<Cont>::Identity(int n)
    {
        return LinAlg::Matrices::Common::Identity<Scalar>(n);
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
    template <typename Cont>
    Matrix<Cont> Matrix<Cont>::randn(int rows, int cols, Scalar mean, Scalar stddev, Scalar min_abs_value, std::optional<int> seed)
    {
        std::mt19937 gen(seed.value_or(std::random_device()()));
        std::normal_distribution<double> dist(mean, stddev);
        Matrix<Cont> result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
            {
                result[i, j] = static_cast<Scalar>(dist(gen));
                while (abs(result[i, j]) < min_abs_value)
                    result[i, j] = static_cast<Scalar>(dist(gen));
            }
        return result;
    }
}
