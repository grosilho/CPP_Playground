cmake --workflow --preset Release
BUILD_DIR="../build/benchmarks_Release"
export CPUPROFILE="${BUILD_DIR}/benchmarks.prof"
export BENCHMARK_OUT="${BUILD_DIR}/benchmark.json"
export BENCHMARK_OUT_FORMAT="json"
EXEC="${BUILD_DIR}/benchmarks"
${EXEC}
pprof --text ${EXEC} ${CPUPROFILE}
