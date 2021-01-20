<<<<<<< HEAD
// Copyright (c) 2015-2018 The DigiByte Core developers
=======
// Copyright (c) 2015-2020 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_BENCH_BENCH_H
#define DIGIBYTE_BENCH_BENCH_H

#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <bench/nanobench.h>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

/*
 * Usage:

static void CODE_TO_TIME(benchmark::Bench& bench)
{
    ... do any setup needed...
    nanobench::Config().run([&] {
       ... do stuff you want to time...
    });
    ... do any cleanup needed...
}

BENCHMARK(CODE_TO_TIME);

 */

namespace benchmark {

using ankerl::nanobench::Bench;

typedef std::function<void(Bench&)> BenchFunction;

struct Args {
    std::string regex_filter;
    bool is_list_only;
    std::vector<double> asymptote;
    std::string output_csv;
    std::string output_json;
};

class BenchRunner
{
    typedef std::map<std::string, BenchFunction> BenchmarkMap;
    static BenchmarkMap& benchmarks();

public:
    BenchRunner(std::string name, BenchFunction func);

    static void RunAll(const Args& args);
};
}
// BENCHMARK(foo) expands to:  benchmark::BenchRunner bench_11foo("foo");
#define BENCHMARK(n) \
    benchmark::BenchRunner BOOST_PP_CAT(bench_, BOOST_PP_CAT(__LINE__, n))(BOOST_PP_STRINGIZE(n), n);

<<<<<<< HEAD

// BENCHMARK(foo, num_iters_for_one_second) expands to:  benchmark::BenchRunner bench_11foo("foo", num_iterations);
// Choose a num_iters_for_one_second that takes roughly 1 second. The goal is that all benchmarks should take approximately
// the same time, and scaling factor can be used that the total time is appropriate for your system.
#define BENCHMARK(n, num_iters_for_one_second) \
    benchmark::BenchRunner BOOST_PP_CAT(bench_, BOOST_PP_CAT(__LINE__, n))(BOOST_PP_STRINGIZE(n), n, (num_iters_for_one_second));

=======
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
#endif // DIGIBYTE_BENCH_BENCH_H
