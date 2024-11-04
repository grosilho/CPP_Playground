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
    Matrix::Matrix (int rows, int cols) : m_rows (rows), m_cols (cols), m_data (std::make_unique<double> (rows * cols))
    {
        m_matrix = stdex::mdspan<double, stdex::dextents<int, 2> > (m_data.get (), rows, cols);
    }

    Matrix::~Matrix () = default;

    std::pair<std::size_t, std::size_t>
    Matrix::size () const
    {
        return std::make_pair (m_rows, m_cols);
    }

    std::size_t
    Matrix::cols () const
    {
        return m_cols;
    }

    std::size_t
    Matrix::rows () const
    {
        return m_rows;
    }
}
