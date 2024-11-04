#include <LinAlg/Matrix.hpp>

namespace LinAlg
{
    /**
     * @brief Construct a new Matrix given the number of rows and columns.
     *
     * Allocates memory but does not initialize it.
     *
     * @param rows
     * @param cols
     */
    template <typename T> Matrix<T>::Matrix (int rows, int cols)
        : m_rows (rows), m_cols (cols), m_data (std::make_unique<T> (rows * cols))
    {
        m_matrix = stdex::mdspan<T, stdex::dextents<int, 2> > (m_data.get (), rows, cols);
    }

    template <typename T> Matrix<T>::~Matrix () = default;

    template <typename T> std::pair<std::size_t, std::size_t>
    Matrix<T>::size () const
    {
        return std::make_pair (m_rows, m_cols);
    }

    template <typename T> std::size_t
    Matrix<T>::cols () const
    {
        return m_cols;
    }

    template <typename T> std::size_t
    Matrix<T>::rows () const
    {
        return m_rows;
    }

    /**
     * Explicitly instantiate the Matrix<double> class.
     */
    template class Matrix<double>;
}
