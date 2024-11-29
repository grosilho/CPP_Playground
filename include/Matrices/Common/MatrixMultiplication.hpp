#pragma once

#include <stdafx.hpp>

namespace LinAlg::Matrices::Common
{
    template <typename Tuple>
    constexpr auto pop_front(Tuple tuple)
    {
        static_assert(std::tuple_size<Tuple>::value > 0, "Cannot pop from an empty tuple");
        return std::apply([](auto, auto... rest) { return std::make_tuple(rest...); }, tuple);
    }

    /**
     * @brief A function to multiply multiple matrices.
     *
     * The pre_eval_expr template parameter is used to force the evaluation of the template expressions before the multiplication.
     * This is useful since matrix multiplication need to access the elements of the matrices multiple times.
     *
     * The variadic template Args is used to accept any number of matrices.
     *
     * @tparam pre_eval_expr if true, the expressions are evaluated before the multiplication
     * @tparam Args matrices types
     * @param args matrices
     * @return Matrix<T> with T being the common scalar type of the matrices
     */
    template <bool pre_eval_expr = false, typename... Args>
    auto mat_mult(Args&&... args)
    {
        if constexpr (pre_eval_expr)
        {
            std::tuple<decltype(std::forward<Args>(args).eval())...> matrices(std::forward<Args>(args).eval()...);
            return mat_mult_impl(matrices);
        }
        else
        {
            std::tuple<Args...> matrices(std::forward<Args>(args)...);
            return mat_mult_impl(matrices);
        }
    }

    template <typename Tuple>
    auto mat_mult_impl(const Tuple& matrices)
    {
        constexpr int N_matrices = std::tuple_size_v<Tuple>;
        static_assert(N_matrices >= 2, "At least two matrices are needed for multiplication.");

        if constexpr (N_matrices == 2)
            return two_matrix_mult(std::get<0>(matrices), std::get<1>(matrices));
        else
            return two_matrix_mult(std::get<0>(matrices), mat_mult_impl(pop_front(matrices)));
    }
}
