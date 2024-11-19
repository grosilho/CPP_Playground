#include <Common/HelperFunctions.hpp>
#include <Matrices/ET/ET.hpp>

namespace ET = LinAlg::Matrices::ET;

using LinAlg::Common::APPROX_EQ;
using LinAlg::Common::DEEP_APPROX_EQ;

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
