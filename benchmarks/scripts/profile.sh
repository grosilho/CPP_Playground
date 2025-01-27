cmake --workflow --preset Release
BUILD_DIR="../build/benchmarks_Release"
EXEC="${BUILD_DIR}/benchmarks"
export BENCHMARK_OUT="results/benchmarks.json"
export BENCHMARK_OUT_FORMAT="json"
export CPUPROFILE="${BUILD_DIR}/benchmarks.prof"
${EXEC}
pprof --text ${EXEC} ${CPUPROFILE}
