#pragma once

#include <LinAlg/Matrix/Derived.hpp>

namespace LinAlg
{
    namespace _implementation_details
    {
        template <typename T>
        concept MatrixType = std::is_base_of<MatrixBase<T>, std::decay_t<T>>::value;

        template <typename T>
        concept ScalarType = std::is_integral_v<T> || std::is_floating_point_v<T>;

        template <MatrixType T>
        auto subscript(const T& t, int i)
        {
            return t[i];
        }

        template <ScalarType T>
        auto subscript(const T& t, int)
        {
            return t;
        }
    }

    template <typename Callable, typename... Args>
    class Expr : public MatrixBase<Expr<Callable, Args...>>
    {
      public:
        using Scalar = CommonScalar<Args...>;

        Expr(Callable callable, const Args&... args)
            : MatrixBase<Expr<Callable, Args...>>(0, 0)
            , m_args(args...)
            , m_callable(callable)
        {
            // bool same_size = (args.size() == ...);
            // assert(same_size && "All matrices must have the same size.");

            this->reinit(std::get<0>(m_args).rows(), std::get<0>(m_args).cols());
        }

        Scalar operator[](int i) const
        {
            using _implementation_details::subscript;
            const auto f = [this, i](const Args&... args) { return m_callable(subscript(args, i)...); };
            return std::apply(f, m_args);
        }
        Scalar operator[](int i, int j) const { return operator[](i*(this->m_cols) + j); }

        Matrix<Scalar> eval() const { return Matrix<Scalar>(*this); }

      private:
        std::tuple<std::conditional_t<traits<Args>::is_leaf::value, const Args&, const Args>...> m_args;
        Callable m_callable;
    };

    namespace _implementation_details
    {
        template <typename T>
        concept AllowedType = MatrixType<T> || ScalarType<T>;
        template <typename T, typename U>
        concept BothScalars = ScalarType<T> && ScalarType<U>;
        template <typename LHS, typename RHS>
        concept AcceptedTypes = AllowedType<LHS> && AllowedType<RHS> && !BothScalars<LHS, RHS>;
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator+(const LHS& lhs, const RHS& rhs)
    {
        return Expr([](auto const& l, auto const& r) { return l + r; }, lhs, rhs);
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator-(const LHS& lhs, const RHS& rhs)
    {
        return Expr([](auto const& l, auto const& r) { return l - r; }, lhs, rhs);
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator*(const LHS& lhs, const RHS& rhs)
    {
        return Expr([](auto const& l, auto const& r) { return l * r; }, lhs, rhs);
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator/(const LHS& lhs, const RHS& rhs)
    {
        return Expr([](auto const& l, auto const& r) { return l / r; }, lhs, rhs);
    }
}
