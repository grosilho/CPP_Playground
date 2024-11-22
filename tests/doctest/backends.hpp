#include <Matrices/Common/HelperFunctions.hpp>
#include <Matrices/ET/ET.hpp>

namespace Common = LinAlg::Matrices::Common;
namespace ET = LinAlg::Matrices::ET;

using LinAlg::Matrices::Common::APPROX_EQ;
using LinAlg::Matrices::Common::DEEP_APPROX_EQ;

/*
    Define helper types containing necessary backends information for the templetized tests.
*/

template <typename T>
struct Common_type
{
    using Scalar = T;
    using OtherScalar = std::conditional_t<std::is_integral_v<Scalar>, double, int>;
    using Matrix = Common::Matrix<Scalar>;
    using OtherMatrix = Common::Matrix<OtherScalar>;
    using Constant = Common::Constant<Scalar>;
    using Zero = Common::Zero<Scalar>;
    using Identity = Common::Identity<Scalar>;
};

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
