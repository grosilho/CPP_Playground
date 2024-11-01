#pragma once

#include <experimental/mdspan>
#include <memory>
#include <utility>

namespace LinAlg
{

    namespace stdex = std::experimental;

    class Matrix
    {
      public:
        Matrix (int rows, int cols);
        ~Matrix ();

        std::pair<std::size_t, std::size_t> size () const; ///< Returns the number of rows and columns.
        std::size_t cols () const;                         ///< Returns the number of columns.
        std::size_t rows () const;                         ///< Returns the number of rows.

      private:
        std::size_t m_rows;
        std::size_t m_cols;
        std::unique_ptr<double> m_data;
        stdex::mdspan<double, stdex::dextents<int, 2> > m_matrix;
    };

}
