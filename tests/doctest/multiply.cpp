#include <doctest/doctest.h>

#include <LinAlg/LinAlg.hpp>
#include <string>

TEST_CASE("multiply_doctest")
{
  CHECK(multiply(2, 3) == 6);
  CHECK(multiply(2, 0) == 0);
  CHECK(multiply(1, 1) == 1);
}

TEST_CASE("multiply_doctest_anotherone")
{
  CHECK(multiply(2, 3) == 6);
  CHECK(multiply(2, 0) == 0);
  CHECK(multiply(1, 1) == 1);
}
