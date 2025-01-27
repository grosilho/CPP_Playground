cmake --workflow --preset Release
BUILD_DIR="../build/benchmarks_Release"
EXEC="${BUILD_DIR}/benchmarks"
export BENCHMARK_OUT="benchmarks.json"
export BENCHMARK_OUT_FORMAT="json"

${EXEC}
python plot_results.py
