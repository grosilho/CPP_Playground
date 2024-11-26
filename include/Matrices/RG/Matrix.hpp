#pragma once
#include <Matrices/Common/Matrix.hpp>
#include <Matrices/RG/Container.hpp>
#include <Matrices/RG/ForwardDeclarations.hpp>

namespace LinAlg::Matrices::RG
{
    template <typename T>
    using Container = _implementation_details::Container<T>;
    template <typename T>
    using Iterator = _implementation_details::Iterator<T>;

    template <typename T>
    class Matrix : public LinAlg::Matrices::Common::Matrix<Container<T>>
    {
      public:
        using Scalar = T;
        using iterator = Container<T>::iterator;
        using const_iterator = Container<T>::const_iterator;

        using LinAlg::Matrices::Common::Matrix<Container<T>>::Matrix;

        // template <std::ranges::sized_range R>
        // Matrix(const R& range)
        //     : Matrix(range.size())
        // {
        //     std::copy(range.begin(), range.end(), this->m_data.begin());
        // }

        iterator begin() { return this->m_data.begin(); }
        iterator end() { return this->m_data.end(); }
        const_iterator begin() const { return this->m_data.begin(); }
        const_iterator end() const { return this->m_data.end(); }
        int size() const { return this->m_data.size(); }

        // template <typename Func>
        // auto apply(Func&& f) const ///< Returns an expression applying the function f to all elements.
        // {
        //     return Expr(std::forward<Func>(f), *this);
        // }
    };

    static_assert(std::ranges::sized_range<Matrix<int>>);
    static_assert(std::ranges::random_access_range<Matrix<int>>);

    using Matrixd = Matrix<double>;
    using Matrixf = Matrix<float>;
    using Matrixi = Matrix<int>;
}
