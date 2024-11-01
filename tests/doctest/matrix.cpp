#include <LinAlg/LinAlg.hpp>
#include <doctest/doctest.h>
#include <string>

TEST_CASE ("matrix_size_1")
{
    LinAlg::Matrix m (3, 4);
    CHECK (m.rows () == 3);
    CHECK (m.cols () == 4);
    CHECK (m.size () == std::make_pair<std::size_t, std::size_t> (3, 4));
}

TEST_CASE ("matrix_size_2")
{
    LinAlg::Matrix m (5, 6);
    CHECK (m.rows () == 5);
    CHECK (m.cols () == 6);
    CHECK (m.size () == std::make_pair<std::size_t, std::size_t> (5, 6));
}
