#include <backends.hpp>
#include <doctest/doctest.h>
#include <iostream>
#include <string>

namespace ImplDet = RG::_implementation_details;

TEST_CASE("RG::Container")
{
    using Cont = ImplDet::Container<int>;

    Cont c1(5);
    CHECK_EQ(c1.size(), 5);

    // operator subscript
    for (int i = 0; i < c1.size(); ++i)
        c1[i] = 2 * i + 1;
    for (int i = 0; i < c1.size(); ++i)
        CHECK_EQ(c1[i], 2 * i + 1);
    // copy constructor and assignment
    Cont c2(c1);
    Cont c3(c1.size() + 2);
    c3 = c1;
    CHECK_EQ(c2.size(), c1.size());
    CHECK_EQ(c3.size(), c1.size());
    for (int i = 0; i < c2.size(); ++i)
    {
        CHECK_EQ(c2[i], 2 * i + 1);
        CHECK_EQ(c3[i], 2 * i + 1);
    }
    // move constructor and assignment
    Cont c4(c1.size() + 2);
    Cont c5(std::move(c3));
    c4 = std::move(c2);
    CHECK_EQ(c4.size(), c1.size());
    CHECK_EQ(c5.size(), c1.size());
    for (int i = 0; i < c4.size(); ++i)
    {
        CHECK_EQ(c4[i], 2 * i + 1);
        CHECK_EQ(c5[i], 2 * i + 1);
    }

    // iterators
    std::vector<int> v1(c1.size());
    std::vector<int> v2(c1.size());
    std::copy(c1.begin(), c1.end(), v1.begin());
    std::copy(c1.cbegin(), c1.cend(), v2.begin());
    for (int i = 0; i < c1.size(); ++i)
    {
        CHECK_EQ(v1[i], 2 * i + 1);
        CHECK_EQ(v2[i], 2 * i + 1);
    }

    const Cont c6(c1);
    std::vector<int> v3(c6.size());
    std::copy(c6.cbegin(), c6.cend(), v3.begin());

    Cont c7(v3);
    CHECK_EQ(c7.size(), c6.size());
    for (int i = 0; i < c7.size(); ++i)
        CHECK_EQ(c7[i], c6[i]);

    const std::vector<int> v4(c6.cbegin(), c6.cend());
    CHECK_EQ(v4.size(), c6.size());
    for (std::size_t i = 0; i < v4.size(); ++i)
        CHECK_EQ(v4[i], c6[i]);
    Cont c8(v4);
    CHECK_EQ(c8.size(), c6.size());
    for (int i = 0; i < c8.size(); ++i)
        CHECK_EQ(c8[i], c6[i]);
}

template <typename Cont>
using MatrixView = RG::MatrixView<Cont>;

TEST_CASE_TEMPLATE("RG::Matrix", S, RG_type<double>)
{
    using Matrix = S::Matrix;

    int rows = 3;
    int cols = 4;
    auto rg = std::views::iota(0) | std::views::take(rows * cols);

    Matrix m1(rows, cols);
    std::copy_n(rg.begin(), rows * cols, m1.data().begin());
    for (int i = 0; i < rows * cols; ++i)
        CHECK_EQ(m1[i], i);

    MatrixView mv1(rows, cols, std::views::iota(0) | std::views::take(rows * cols));
    MatrixView mv2(rows, cols, rg);
    for (int i = 0; i < rows * cols; ++i)
        CHECK_EQ(mv1[i], i);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            CHECK_EQ(mv2[i, j], i * cols + j);
    {
        int i = 0;
        for (auto m : mv1)
        {
            CHECK_EQ(m, i);
            i++;
        }
    }

    MatrixView mv3(mv1);
    for (int i = 0; i < rows * cols; ++i)
        CHECK_EQ(mv3[i], i);

    Matrix m2(mv1);
    CHECK(APPROX_EQ(mv1, m2));

    auto m3 = mv1.eval();
    CHECK(APPROX_EQ(mv1, m3));

    Matrix m4 = mv1 + mv2;
    for (int i = 0; i < rows * cols; ++i)
        CHECK_EQ(m4[i], mv1[i] + mv2[i]);

    Matrix m5 = (1 + mv1) + 1;
    for (int i = 0; i < rows * cols; ++i)
        CHECK_EQ(m5[i], mv1[i] + 2);

    for (int i = 0; i < m1.rows(); i++)
    {
        auto row = m1.row(i);
        for (int j = 0; j < m1.cols(); j++)
            CHECK_EQ(row[j], m1[i, j]);
    }
    for (int j = 0; j < m1.cols(); j++)
    {
        auto col = m1.col(j);
        for (int i = 0; i < m1.rows(); i++)
            CHECK_EQ(col[i], m1[i, j]);
    }
}
