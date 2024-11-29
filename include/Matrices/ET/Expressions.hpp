#pragma once

#include <Matrices/ET/Concepts.hpp>
#include <Matrices/ET/ForwardDeclarations.hpp>
#include <Matrices/ET/Matrix.hpp>

namespace LinAlg::Matrices::ET
{
    namespace _implementation_details
    {
        template <Concepts::MatrixType T>
        auto subscript(const T& t, int i)
        {
            return t[i];
        }

        template <Concepts::ScalarType T>
        auto subscript(const T& t, int)
        {
            return t;
        }
    }

    template <typename Callable, typename... Args>
    class Expr : public MatrixBase<Expr<Callable, Args...>>
    {
      public:
        using Scalar = LinAlg::CommonScalar<Args...>;

        template <typename Func, typename... Matrices>
        Expr(Func&& callable, Matrices&&... mats)
            : MatrixBase<Expr<Func, Matrices...>>(0, 0)
            , m_args(std::forward<Matrices>(mats)...)
            , m_callable(std::forward<Func>(callable))
        {
            this->reinit(std::get<0>(m_args).rows(), std::get<0>(m_args).cols());
        }

        Expr(int rows, int cols) = delete;
        Expr(const Expr&) = delete;
        Expr& operator=(const Expr&) = delete;

        Expr(Expr&&) = default;
        Expr& operator=(Expr&&) = default;

        Scalar operator[](int i) const
        {
            using _implementation_details::subscript;

            const auto f = [this, i](const Args&... args) { return m_callable(subscript(args, i)...); };
            return std::apply(f, m_args);
        }

        Scalar operator[](int i, int j) const { return operator[](i*(this->m_cols) + j); }

        Matrix<Scalar> eval() const& = delete;
        Matrix<Scalar> eval() const&& { return Matrix<Scalar>(*this); }

      private:
        std::tuple<Args...> m_args;
        Callable m_callable;
    };

    template <typename Func, typename... Matrices>
    Expr(Func&&, Matrices&&...) -> Expr<Func, Matrices...>;

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator+(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for addition.");

        return Expr([](auto const& l, auto const& r) { return l + r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator-(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for substraction.");

        return Expr([](auto const& l, auto const& r) { return l - r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator*(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for coefficient wise multiplication.");

        return Expr([](auto const& l, auto const& r) { return l * r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires Concepts::AcceptedTypes<LHS, RHS>
    auto operator/(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (Concepts::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for coefficient wise division.");

        return Expr([](auto const& l, auto const& r) { return l / r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

}
