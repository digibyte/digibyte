<<<<<<< HEAD
// Copyright (c) 2015-2018 The DigiByte Core developers
=======
// Copyright (c) 2015-2020 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/bench.h>

// Extremely fast-running benchmark:
#include <math.h>

volatile double sum = 0.0; // volatile, global so not optimized away

static void Trig(benchmark::Bench& bench)
{
    double d = 0.01;
    bench.run([&] {
        sum += sin(d);
        d += 0.000001;
    });
}

BENCHMARK(Trig);
