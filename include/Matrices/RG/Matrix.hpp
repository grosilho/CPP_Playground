#pragma once
#include <Matrices/Common/Matrix.hpp>
#include <Matrices/RG/Container.hpp>
#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename Cont>
        requires Concepts::sized_output_random_access_range<Cont>
    class MatrixCont : public LinAlg::Matrices::Common::Matrix<Cont>, public _implementation_details::RangeWrapper<MatrixCont<Cont>>
    {
      public:
        using Scalar = std::ranges::range_value_t<Cont>;
        using iterator = std::ranges::iterator_t<Cont>;
        using const_iterator = std::ranges::const_iterator_t<Cont>;
        using RGType = Cont;

        using LinAlg::Matrices::Common::Matrix<Cont>::Matrix;

        template <std::ranges::view View>
        MatrixCont(const MatrixView<View>& mat_view)
            : MatrixCont(mat_view.rows(), mat_view.cols())
        {
            std::copy_n(mat_view.begin(), this->rows() * this->cols(), this->begin());
        }

        Cont& data() { return this->m_data; }
        const Cont& data() const { return this->m_data; }

        template <typename Func>
        auto apply(Func&& f) const
        {
            auto apply_f = *this | std::views::transform(std::forward<Func>(f));
            return MatrixView(this->rows(), this->cols(), apply_f);
        }
    };

    template <typename T>
    using Matrix = MatrixCont<Container<T>>;

    static_assert(std::ranges::random_access_range<Matrix<int>>);

    using Matrixd = Matrix<double>;
    using Matrixf = Matrix<float>;
    using Matrixi = Matrix<int>;
}
