#include <benchmark/benchmark.h>

#include <vector>

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "table.h"

#define MCA_START __asm volatile("# LLVM-MCA-BEGIN");
#define MCA_END __asm volatile("# LLVM-MCA-END");

using namespace omni;

static void BM_CreateNxNDynamicTable(benchmark::State& state) {
  
  for (auto _ : state) {
    Table table;
    for (int i = 0; i < state.range(0); i++) {
      for (int j = 0; j < state.range(1); j++) {
        table[i][j] = "Text";
      }
    }
  }

}
// Register the function as a benchmark
BENCHMARK(BM_CreateNxNDynamicTable)
  ->Args({1,1})
  ->Args({1,2})
  ->Args({1,10})
  ->Args({1,100})
  ->Args({2,1})
  ->Args({10,1})
  ->Args({100,1})
  ->Args({10, 10})
  ->Args({50, 50})
  ->Args({100, 100})
  ->Args({1000, 1000});

BENCHMARK_MAIN();
