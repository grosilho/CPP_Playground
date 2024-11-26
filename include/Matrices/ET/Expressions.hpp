#pragma once

#include <Matrices/ET/Matrix.hpp>

namespace LinAlg::Matrices::ET
{
    namespace _implementation_details
    {
        template <typename T>
        concept MatrixType = std::is_base_of_v<MatrixBase<std::remove_cvref_t<T>>, std::remove_cvref_t<T>>
            || std::is_same_v<Matrix<typename LinAlg::_implementation_details::traits<std::remove_cvref_t<T>>::Scalar>, std::remove_cvref_t<T>>;

        template <typename T>
        concept ScalarType = std::is_integral_v<std::remove_cvref_t<T>> || std::is_floating_point_v<std::remove_cvref_t<T>>;

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
        using Scalar = LinAlg::_implementation_details::CommonScalar<Args...>;

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

    namespace _implementation_details
    {
        template <typename T>
        concept AllowedType = MatrixType<T> || ScalarType<T>;
        template <typename T, typename U>
        concept BothScalars = ScalarType<T> && ScalarType<U>;
        template <typename T, typename U>
        concept BothMatrices = MatrixType<T> && MatrixType<U>;
        template <typename LHS, typename RHS>
        concept AcceptedTypes = AllowedType<LHS> && AllowedType<RHS> && !BothScalars<LHS, RHS>;
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator+(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (_implementation_details::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for addition.");

        return Expr([](auto const& l, auto const& r) { return l + r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator-(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (_implementation_details::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for substraction.");

        return Expr([](auto const& l, auto const& r) { return l - r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator*(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (_implementation_details::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for coefficient wise multiplication.");

        return Expr([](auto const& l, auto const& r) { return l * r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

    template <typename LHS, typename RHS>
        requires _implementation_details::AcceptedTypes<LHS, RHS>
    auto operator/(LHS&& lhs, RHS&& rhs)
    {
        if constexpr (_implementation_details::BothMatrices<LHS, RHS>)
            assert(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols() && "Matrix dimensions do not match for coefficient wise division.");

        return Expr([](auto const& l, auto const& r) { return l / r; }, std::forward<LHS>(lhs), std::forward<RHS>(rhs));
    }

}
