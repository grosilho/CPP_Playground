#pragma once
#include <Matrices/Common/Base.hpp>
#include <Matrices/RG/Container.hpp>
#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename T>
    using Container = _implementation_details::Container<T>;

    template <std::ranges::view View>
    class MatrixView : public LinAlg::Matrices::Common::MatrixBase<MatrixView<View>>,
                       public _implementation_details::RangeWrapper<MatrixView<View>>,
                       public std::ranges::view_interface<MatrixView<View>>
    {
      public:
        using Scalar = std::ranges::range_value_t<View>;
        using iterator = std::ranges::iterator_t<View>;
        using const_iterator = std::ranges::const_iterator_t<View>;
        using RGType = View;

        template <typename V>
        MatrixView(int rows, int cols, V&& view)
            : LinAlg::Matrices::Common::MatrixBase<MatrixView<View>>(rows, cols)
            , m_view(std::forward<V>(view)) // copy and move have same efficency for views
        {
        }

        template <typename Cont = Container<Scalar>>
        MatrixCont<Cont> eval() const
        {
            return MatrixCont<Cont>(*this);
        }

        Scalar operator[](int i, int j) const { return m_view[i * this->m_cols + j]; }; ///< Access the element at row i and column j.
        Scalar operator[](int i) const { return m_view[i]; };                           ///< Access the element i in the flattened matrix.

        View& data() { return m_view; }
        const View& data() const { return m_view; }

      private:
        View m_view;
    };

    template <typename V>
    MatrixView(int, int, V&&) -> MatrixView<std::remove_cvref_t<V>>;
}
