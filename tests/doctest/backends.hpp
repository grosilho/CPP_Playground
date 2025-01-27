#include <Matrices/Common/HelperFunctions.hpp>
#include <Matrices/ET/ET.hpp>
#include <Matrices/RG/RG.hpp>

namespace ET = LinAlg::Matrices::ET;
namespace RG = LinAlg::Matrices::RG;

using LinAlg::Matrices::Common::APPROX_EQ;
using LinAlg::Matrices::Common::DEEP_APPROX_EQ;

/*
    Define helper types containing necessary backends information for the templetized tests.
*/

template <typename T>
struct ET_type
{
    using Scalar = T;
    using OtherScalar = std::conditional_t<std::is_integral_v<Scalar>, double, int>;
    using Matrix = ET::Matrix<Scalar>;
    using OtherMatrix = ET::Matrix<OtherScalar>;
    using Constant = ET::Constant<Scalar>;
    using Zero = ET::Zero<Scalar>;
    using Identity = ET::Identity<Scalar>;
};

template <typename T>
struct RG_type
{
    using Scalar = T;
    using OtherScalar = std::conditional_t<std::is_integral_v<Scalar>, double, int>;
    using Matrix = RG::Matrix<Scalar>;
    using OtherMatrix = RG::Matrix<OtherScalar>;
    using Constant = RG::Constant<Scalar>;
    using Zero = RG::Zero<Scalar>;
    using Identity = RG::Identity<Scalar>;
};

template <typename T>
struct RG_type_STL
{
    using Scalar = T;
    using OtherScalar = std::conditional_t<std::is_integral_v<Scalar>, double, int>;
    using Matrix = RG::MatrixCont<std::vector<Scalar>>;
    using OtherMatrix = RG::Matrix<std::vector<OtherScalar>>;
    using Constant = RG::Constant<Scalar>;
    using Zero = RG::Zero<Scalar>;
    using Identity = RG::Identity<Scalar>;
};
