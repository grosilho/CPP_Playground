#pragma once

#include <Matrices/ET_CRTP/Base.hpp>
#include <Matrices/ET_CRTP/Expressions.hpp>
#include <Matrices/ET_CRTP/HelperMatrices.hpp>
#include <Matrices/ET_CRTP/Matrix.hpp>
#include <Matrices/ET_CRTP/MatrixMultiplication.hpp>

namespace LinAlg::Matrices::ET_CRTP
{
    using Matrixd = Matrix<double>;
    using Matrixf = Matrix<float>;
    using Matrixi = Matrix<int>;
}
