#pragma once

#include "benchmarks.hpp"

extern double min_time;
extern double min_warmup_time;
extern int range_min;
extern int squared_compl_range_max;
extern int cubic_compl_range_max;
extern int range_mult;

// Allocate ---------------------------------------------------------------------
BENCHMARK(allocate_matrix<RG_type_STL<double>::Matrix>)
    ->Name("allocate_matrix_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(allocate_matrix<RG_type<double>::Matrix>)
    ->Name("allocate_matrix_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Set operator -----------------------------------------------------------------
BENCHMARK(set_operator<RG_type_STL<double>::Matrix>)
    ->Name("operator[]_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(set_operator<RG_type<double>::Matrix>)
    ->Name("operator[]_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Copy operator -----------------------------------------------------------------
BENCHMARK(copy_operator<RG_type_STL<double>::Matrix>)
    ->Name("copy_matrix_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(copy_operator<RG_type<double>::Matrix>)
    ->Name("copy_matrix_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Move operator -----------------------------------------------------------------
BENCHMARK(move_operator<RG_type_STL<double>::Matrix>)
    ->Name("move_matrix_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::o1);
BENCHMARK(move_operator<RG_type<double>::Matrix>)
    ->Name("move_matrix_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::o1);

// apply operator -----------------------------------------------------------------
BENCHMARK(apply_operator<RG_type_STL<double>::Matrix>)
    ->Name("apply_fun_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(apply_operator<RG_type<double>::Matrix>)
    ->Name("apply_fun_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// apply_inplace operator -----------------------------------------------------------------
BENCHMARK(apply_inplace_operator<RG_type_STL<double>::Matrix>)
    ->Name("apply_inplace_fun_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(apply_inplace_operator<RG_type<double>::Matrix>)
    ->Name("apply_inplace_fun_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// LU factorization -----------------------------------------------------------------
BENCHMARK(LU_factorization<RG_type_STL<double>::Matrix>)
    ->Name("LU_factorization_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(LU_factorization<RG_type<double>::Matrix>)
    ->Name("LU_factorization_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// Mult two matrices -----------------------------------------------------------------
BENCHMARK(mult_two_matrices<RG_type_STL<double>::Matrix>)
    ->Name("mult_two_mat_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_two_matrices<RG_type<double>::Matrix>)
    ->Name("mult_two_mat_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// Mult four matrices -----------------------------------------------------------------
BENCHMARK(mult_four_matrices<RG_type_STL<double>::Matrix>)
    ->Name("mult_four_mat_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_four_matrices<RG_type<double>::Matrix>)
    ->Name("mult_four_mat_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// LU solve -----------------------------------------------------------------
BENCHMARK(LU_solve<RG_type_STL<double>::Matrix>)
    ->Name("LU_solve_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(LU_solve<RG_type<double>::Matrix>)
    ->Name("LU_solve_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// long operation -----------------------------------------------------------------
BENCHMARK(long_op_matrices<RG_type_STL<double>::Matrix>)
    ->Name("long_op_1_STL")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(long_op_matrices<RG_type<double>::Matrix>)
    ->Name("long_op_1_CST")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
