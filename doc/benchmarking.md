Benchmarking
============

DigiByte Core has an internal benchmarking framework, with benchmarks
<<<<<<< HEAD
for cryptographic algorithms (e.g. SHA1, SHA256, SHA512, RIPEMD160), as well as the rolling bloom filter.

Running
---------------------
After compiling digibyte-core, the benchmarks can be run with:

=======
for cryptographic algorithms (e.g. SHA1, SHA256, SHA512, RIPEMD160, Poly1305, ChaCha20), rolling bloom filter, coins selection,
thread queue, wallet balance.

Running
---------------------

For benchmarks purposes you only need to compile `digibyte_bench`. Beware of configuring without `--enable-debug` as this would impact
benchmarking by unlatching log printers and lock analysis.

    make -C src digibyte_bench

After compiling digibyte-core, the benchmarks can be run with:

>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
    src/bench/bench_digibyte

The output will look similar to:
```
|             ns/byte |              byte/s | error % | benchmark
|--------------------:|--------------------:|--------:|:----------------------------------------------
|               64.13 |       15,592,356.01 |    0.1% | `Base58CheckEncode`
|               24.56 |       40,722,672.68 |    0.2% | `Base58Decode`
...
```

Help
---------------------

<<<<<<< HEAD
    src/bench/bench_digibyte -?
=======
    src/bench/bench_digibyte --help

To print options like scaling factor or per-benchmark filter.
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

Notes
---------------------
More benchmarks are needed for, in no particular order:
- Script Validation
- Coins database
- Memory pool
- Cuckoo Cache
- P2P throughput

Going Further
--------------------

To monitor DigiByte Core performance more in depth (like reindex or IBD): https://github.com/chaincodelabs/digibyteperf

To generate Flame Graphs for DigiByte Core: https://github.com/eklitzke/digibyte/blob/flamegraphs/doc/flamegraphs.md
