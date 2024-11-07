#include <doctest/doctest.h>
#include <iostream>
#include <string>

import LinAlg;

TEST_CASE ("Matrix::size,rows,cols")
{
    LinAlg::Matrix<double> m1 (3, 4);
    CHECK_EQ (m1.rows (), 3);
    CHECK_EQ (m1.cols (), 4);
    CHECK_EQ (m1.size (), std::make_pair<std::size_t, std::size_t> (3, 4));

    LinAlg::Matrix<double> m2 (5, 6);
    CHECK_EQ (m2.rows (), 5);
    CHECK_EQ (m2.cols (), 6);
    CHECK_EQ (m2.size (), std::make_pair<std::size_t, std::size_t> (5, 6));
}

TEST_CASE ("Matrix::operator[]")
{
    LinAlg::Matrix<double> m (3, 4);
    for (std::size_t i = 0; i < m.rows (); ++i)
        for (std::size_t j = 0; j < m.cols (); ++j)
            m[i, j] = i * m.cols () + j;

    for (std::size_t i = 0; i < m.rows (); ++i)
        for (std::size_t j = 0; j < m.cols (); ++j)
            CHECK_EQ (m[i, j], i * m.cols () + j);
}

TEST_CASE ("Matrix::copy and move")
{
    LinAlg::Matrix<double> m1 (3, 4);
    for (std::size_t i = 0; i < m1.rows (); ++i)
        for (std::size_t j = 0; j < m1.cols (); ++j)
            m1[i, j] = i * m1.cols () + j;

    SUBCASE ("copy constructor")
    {
        LinAlg::Matrix<double> m2 (m1);
        CHECK_EQ (m1.size (), m2.size ());
        CHECK_EQ (m1.rows (), m2.rows ());
        CHECK_EQ (m1.cols (), m2.cols ());
        for (std::size_t i = 0; i < m1.rows (); ++i)
            for (std::size_t j = 0; j < m1.cols (); ++j)
                CHECK_EQ (m1[i, j], m2[i, j]);
    }
    SUBCASE ("copy assignment")
    {
        LinAlg::Matrix<double> m2 (0, 0);
        m2 = m1;
        CHECK_EQ (m1.size (), m2.size ());
        CHECK_EQ (m1.rows (), m2.rows ());
        CHECK_EQ (m1.cols (), m2.cols ());
        for (std::size_t i = 0; i < m1.rows (); ++i)
            for (std::size_t j = 0; j < m1.cols (); ++j)
                CHECK_EQ (m1[i, j], m2[i, j]);
    }
    SUBCASE ("move constructor")
    {
        LinAlg::Matrix<double> m1_copy (m1);
        LinAlg::Matrix<double> m2 (std::move (m1));
        CHECK_EQ (m1.size (), std::make_pair<std::size_t, std::size_t> (0, 0));
        CHECK_EQ (m1.rows (), 0);
        CHECK_EQ (m1.cols (), 0);
        CHECK_EQ (m1_copy.size (), m2.size ());
        CHECK_EQ (m1_copy.rows (), m2.rows ());
        CHECK_EQ (m1_copy.cols (), m2.cols ());
        for (std::size_t i = 0; i < m1_copy.rows (); ++i)
            for (std::size_t j = 0; j < m1_copy.cols (); ++j)
                CHECK_EQ (m1_copy[i, j], m2[i, j]);
    }
    SUBCASE ("move assignment")
    {
        LinAlg::Matrix<double> m1_copy (m1);
        LinAlg::Matrix<double> m2 (0, 0);
        m2 = std::move (m1);
        CHECK_EQ (m1.size (), std::make_pair<std::size_t, std::size_t> (0, 0));
        CHECK_EQ (m1.rows (), 0);
        CHECK_EQ (m1.cols (), 0);
        CHECK_EQ (m1_copy.size (), m2.size ());
        CHECK_EQ (m1_copy.rows (), m2.rows ());
        CHECK_EQ (m1_copy.cols (), m2.cols ());
        for (std::size_t i = 0; i < m1_copy.rows (); ++i)
            for (std::size_t j = 0; j < m1_copy.cols (); ++j)
                CHECK_EQ (m1_copy[i, j], m2[i, j]);
    }
}

TEST_CASE ("Matrix::Identity")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Identity (3);
    CHECK_EQ (m.rows (), 3);
    CHECK_EQ (m.cols (), 3);
    for (std::size_t i = 0; i < m.rows (); ++i)
        for (std::size_t j = 0; j < m.cols (); ++j)
            if (i == j)
                CHECK_EQ (m[i, j], 1);
            else
                CHECK_EQ (m[i, j], 0);
}

TEST_CASE ("Matrix::Zero")
{
    LinAlg::Matrix<int> m = LinAlg::Matrix<int>::Zero (3, 4);
    CHECK_EQ (m.rows (), 3);
    CHECK_EQ (m.cols (), 4);
    for (std::size_t i = 0; i < m.rows (); ++i)
        for (std::size_t j = 0; j < m.cols (); ++j)
            CHECK_EQ (m[i, j], 0);
}

TEST_CASE ("Matrix::swap")
{
    LinAlg::Matrix<int> m1 (3, 4);
    for (std::size_t i = 0; i < m1.rows (); ++i)
        for (std::size_t j = 0; j < m1.cols (); ++j)
            m1[i, j] = i * m1.cols () + j;

    LinAlg::Matrix<int> m2 (5, 6);
    for (std::size_t i = 0; i < m2.rows (); ++i)
        for (std::size_t j = 0; j < m2.cols (); ++j)
            m2[i, j] = i * m2.cols () + j;

    LinAlg::Matrix<int> m1_copy (m1);
    LinAlg::Matrix<int> m2_copy (m2);

    swap (m1, m2);

    CHECK_EQ (m1.size (), m2_copy.size ());
    CHECK_EQ (m1.rows (), m2_copy.rows ());
    CHECK_EQ (m1.cols (), m2_copy.cols ());
    for (std::size_t i = 0; i < m1.rows (); ++i)
        for (std::size_t j = 0; j < m1.cols (); ++j)
            CHECK_EQ (m1[i, j], m2_copy[i, j]);

    CHECK_EQ (m2.size (), m1_copy.size ());
    CHECK_EQ (m2.rows (), m1_copy.rows ());
    CHECK_EQ (m2.cols (), m1_copy.cols ());
    for (std::size_t i = 0; i < m2.rows (); ++i)
        for (std::size_t j = 0; j < m2.cols (); ++j)
            CHECK_EQ (m2[i, j], m1_copy[i, j]);
}
