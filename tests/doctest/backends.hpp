#include <Common/HelperFunctions.hpp>
#include <Matrices/ET_CRTP/ET_CRTP.hpp>

namespace ET_CRTP = LinAlg::Matrices::ET_CRTP;

using LinAlg::Common::APPROX_EQ;
using LinAlg::Common::DEEP_APPROX_EQ;

/*
    Define helper types containing necessary backends information for the templetized tests.
*/

template <typename T>
struct ET_CRTP_type
{
    using Scalar = T;
    using OtherScalar = std::conditional_t<std::is_integral_v<Scalar>, double, int>;
    using Matrix = ET_CRTP::Matrix<Scalar>;
    using OtherMatrix = ET_CRTP::Matrix<OtherScalar>;
    using Constant = ET_CRTP::Constant<Scalar>;
    using Zero = ET_CRTP::Zero<Scalar>;
    using Identity = ET_CRTP::Identity<Scalar>;
};
