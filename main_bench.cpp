#include <benchmark/benchmark.h>
#include <set>
#include "headers/Set.hpp"

// ========================= Custom Set vs std::set ==========================

// Insert
static void BM_CustomSet_Insert(benchmark::State& state) {
    for (auto _ : state) {
        Set<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.insert(i);
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_CustomSet_Insert)->Range(1 << 10, 1 << 18); // 1K – 256K

static void BM_StdSet_Insert(benchmark::State& state) {
    for (auto _ : state) {
        std::set<int> s;
        for (int i = 0; i < state.range(0); ++i) {
            s.insert(i);
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_StdSet_Insert)->Range(1 << 10, 1 << 18);

// Find
static void BM_CustomSet_Find(benchmark::State& state) {
    Set<int> s;
    for (int i = 0; i < state.range(0); ++i) s.insert(i);

    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            s.find(i);
        }
    }
}
BENCHMARK(BM_CustomSet_Find)->Range(1 << 10, 1 << 18);

static void BM_StdSet_Find(benchmark::State& state) {
    std::set<int> s;
    for (int i = 0; i < state.range(0); ++i) s.insert(i);

    for (auto _ : state) {
        for (int i = 0; i < state.range(0); ++i) {
            s.find(i);
        }
    }
}
BENCHMARK(BM_StdSet_Find)->Range(1 << 10, 1 << 18);

// Erase
static void BM_CustomSet_Erase(benchmark::State& state) {
    for (auto _ : state) {
        Set<int> s;
        for (int i = 0; i < state.range(0); ++i) s.insert(i);

        for (int i = 0; i < state.range(0); ++i) {
            s.erase(i);
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_CustomSet_Erase)->Range(1 << 10, 1 << 18);

static void BM_StdSet_Erase(benchmark::State& state) {
    for (auto _ : state) {
        std::set<int> s;
        for (int i = 0; i < state.range(0); ++i) s.insert(i);

        for (int i = 0; i < state.range(0); ++i) {
            s.erase(i);
        }
        benchmark::DoNotOptimize(s);
    }
}
BENCHMARK(BM_StdSet_Erase)->Range(1 << 10, 1 << 18);

// ========================= Main ==========================
BENCHMARK_MAIN();
