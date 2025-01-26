#include "benchmarks.hpp"

double min_time = 1.0;
double min_warmup_time = 1.0;
int range_min = 2;
int squared_compl_range_max = 2 << 11;
int cubic_compl_range_max = 2 << 8;
int range_mult = 8;

// Allocate ---------------------------------------------------------------------
BENCHMARK(allocate_matrix<ET_type<double>::Matrix>)
    ->Name("allocate_matrix_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(allocate_matrix<RG_type<double>::Matrix>)
    ->Name("allocate_matrix_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Set operator -----------------------------------------------------------------
BENCHMARK(set_operator<ET_type<double>::Matrix>)
    ->Name("operator[]_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(set_operator<RG_type<double>::Matrix>)
    ->Name("operator[]_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Copy operator -----------------------------------------------------------------
BENCHMARK(copy_operator<ET_type<double>::Matrix>)
    ->Name("copy_matrix_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(copy_operator<RG_type<double>::Matrix>)
    ->Name("copy_matrix_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Move operator -----------------------------------------------------------------
BENCHMARK(move_operator<ET_type<double>::Matrix>)
    ->Name("move_matrix_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::o1);
BENCHMARK(move_operator<RG_type<double>::Matrix>)
    ->Name("move_matrix_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::o1);

// apply operator -----------------------------------------------------------------
BENCHMARK(apply_operator<ET_type<double>::Matrix>)
    ->Name("apply_fun_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(apply_operator<RG_type<double>::Matrix>)
    ->Name("apply_fun_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// apply_inplace operator -----------------------------------------------------------------
BENCHMARK(apply_inplace_operator<ET_type<double>::Matrix>)
    ->Name("apply_inplace_fun_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(apply_inplace_operator<RG_type<double>::Matrix>)
    ->Name("apply_inplace_fun_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Sum two matrices -----------------------------------------------------------------
BENCHMARK(sum_two<ET_type<double>::Matrix>)
    ->Name("sum_two_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(sum_two<RG_type<double>::Matrix>)
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
BENCHMARK(sum_four<RG_type<double>::Matrix>)
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
BENCHMARK(mult_two_elwise<RG_type<double>::Matrix>)
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
BENCHMARK(mult_four_elwise<RG_type<double>::Matrix>)
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
BENCHMARK(sum_scalar<RG_type<double>::Matrix>)
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
BENCHMARK(mult_scalar<RG_type<double>::Matrix>)
    ->Name("mult_with_scalar_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, squared_compl_range_max)
    ->Complexity(benchmark::oNSquared);

// Mult two matrices -----------------------------------------------------------------
BENCHMARK(mult_two_matrices<ET_type<double>::Matrix>)
    ->Name("mult_two_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_two_matrices<RG_type<double>::Matrix>)
    ->Name("mult_two_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// Mult four matrices -----------------------------------------------------------------
BENCHMARK(mult_four_matrices<ET_type<double>::Matrix>)
    ->Name("mult_four_mat_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_four_matrices<RG_type<double>::Matrix>)
    ->Name("mult_four_mat_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// Mult two expr -----------------------------------------------------------------
BENCHMARK(mult_two_expr<ET_type<double>::Matrix>)
    ->Name("mult_two_expr_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(mult_two_expr<RG_type<double>::Matrix>)
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
BENCHMARK(mult_two_expr_preeval<RG_type<double>::Matrix>)
    ->Name("mult_two_expr_preeval_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// LU factorization -----------------------------------------------------------------
BENCHMARK(LU_factorization<ET_type<double>::Matrix>)
    ->Name("LU_factorization_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);
BENCHMARK(LU_factorization<RG_type<double>::Matrix>)
    ->Name("LU_factorization_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNCubed);

// LU solve -----------------------------------------------------------------
BENCHMARK(LU_solve<ET_type<double>::Matrix>)
    ->Name("LU_solve_ET")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNSquared);
BENCHMARK(LU_solve<RG_type<double>::Matrix>)
    ->Name("LU_solve_RG")
    ->MinTime(min_time)
    ->MinWarmUpTime(min_warmup_time)
    ->RangeMultiplier(range_mult)
    ->Range(range_min, cubic_compl_range_max)
    ->Complexity(benchmark::oNSquared);

BENCHMARK_MAIN();
