#pragma once

#include "benchmarks.hpp"

extern double min_time;
extern double min_warmup_time;
extern int range_min;
extern int squared_compl_range_max;
extern int cubic_compl_range_max;
extern int range_mult;

// Sum two matrices -----------------------------------------------------------------
BENCHMARK(sum_two<ET_type<double>::Matrix>)
    ->Name("sum_two_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(sum_two<RG_type_STL<double>::Matrix>)
    ->Name("sum_two_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Sum four matrices -----------------------------------------------------------------
BENCHMARK(sum_four<ET_type<double>::Matrix>)
    ->Name("sum_four_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(sum_four<RG_type_STL<double>::Matrix>)
    ->Name("sum_four_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Mult two matrices element wise -----------------------------------------------------------------
BENCHMARK(mult_two_elwise<ET_type<double>::Matrix>)
    ->Name("mult_elwise_two_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(mult_two_elwise<RG_type_STL<double>::Matrix>)
    ->Name("mult_elwise_two_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Mult four matrices element wise -----------------------------------------------------------------
BENCHMARK(mult_four_elwise<ET_type<double>::Matrix>)
    ->Name("mult_elwise_four_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(mult_four_elwise<RG_type_STL<double>::Matrix>)
    ->Name("mult_elwise_four_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Sum with scalar -----------------------------------------------------------------
BENCHMARK(sum_scalar<ET_type<double>::Matrix>)
    ->Name("sum_with_scalar_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(sum_scalar<RG_type_STL<double>::Matrix>)
    ->Name("sum_with_scalar_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Mult with scalar -----------------------------------------------------------------
BENCHMARK(mult_scalar<ET_type<double>::Matrix>)
    ->Name("mult_with_scalar_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(mult_scalar<RG_type_STL<double>::Matrix>)
    ->Name("mult_with_scalar_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Mult two expr -----------------------------------------------------------------
BENCHMARK(mult_two_expr<ET_type<double>::Matrix>)
    ->Name("mult_two_expr_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_two_expr<RG_type_STL<double>::Matrix>)
    ->Name("mult_two_expr_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// Mult two expr preeval -----------------------------------------------------------------
BENCHMARK(mult_two_expr_preeval<ET_type<double>::Matrix>)
    ->Name("mult_two_expr_preeval_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_two_expr_preeval<RG_type_STL<double>::Matrix>)
    ->Name("mult_two_expr_preeval_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// long operation -----------------------------------------------------------------
BENCHMARK(long_op_matrices<ET_type<double>::Matrix>)
    ->Name("long_op_2_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(long_op_matrices<RG_type_STL<double>::Matrix>)
    ->Name("long_op_2_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
