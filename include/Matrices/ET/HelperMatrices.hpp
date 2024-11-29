#pragma once

#include <Matrices/Common/HelperMatrices.hpp>

namespace LinAlg::Matrices::ET
{
    template <typename T>
    using Constant = LinAlg::Matrices::Common::Constant<T>;

    template <typename T>
    using Zero = LinAlg::Matrices::Common::Zero<T>;

    template <typename T>
    using Identity = LinAlg::Matrices::Common::Identity<T>;
}
