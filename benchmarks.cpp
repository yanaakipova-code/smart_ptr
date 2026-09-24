#include <benchmark/benchmark.h>
#include <memory>

#include "smart/unic_ptr.hpp"
#include "smart/share_ptr.hpp"

void b_m_raw(benchmark::State& state) {
    for (auto x : state) {
        int* p = new int(42);
        benchmark::DoNotOptimize(p);
        delete p;
    }
}
BENCHMARK(b_m_raw);

void b_m_unic_ptr(benchmark::State& state) {
    for (auto x : state) {
        unique_ptr<int> p(new int(42));
        benchmark::DoNotOptimize(p);
    }
}
BENCHMARK(b_m_unic_ptr);

void b_m_share_ptr(benchmark::State& state) {
    for (auto x : state) {
        share_ptr<int> p(new int(42));
        benchmark::DoNotOptimize(p);
    }
}
BENCHMARK(b_m_share_ptr);

void b_m_stl_unique(benchmark::State& state) {
    for (auto x : state) {
        std::unique_ptr<int> p(new int(42));
        benchmark::DoNotOptimize(p);
    }
}
BENCHMARK(b_m_stl_unique);

void b_m_stl_shared(benchmark::State& state) {
    for (auto x : state) {
        std::shared_ptr<int> p(new int(42));
        benchmark::DoNotOptimize(p);
    }
}
BENCHMARK(b_m_stl_shared);

BENCHMARK_MAIN();