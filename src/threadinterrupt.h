<<<<<<< HEAD
// Copyright (c) 2016-2017 The DigiByte Core developers
=======
// Copyright (c) 2016-2019 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_THREADINTERRUPT_H
#define DIGIBYTE_THREADINTERRUPT_H
<<<<<<< HEAD
=======

#include <sync.h>
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25

#include <atomic>
#include <chrono>
#include <condition_variable>

/*
    A helper class for interruptible sleeps. Calling operator() will interrupt
    any current sleep, and after that point operator bool() will return true
    until reset.
*/
class CThreadInterrupt
{
public:
    CThreadInterrupt();
    explicit operator bool() const;
    void operator()();
    void reset();
    bool sleep_for(std::chrono::milliseconds rel_time);
    bool sleep_for(std::chrono::seconds rel_time);
    bool sleep_for(std::chrono::minutes rel_time);

private:
    std::condition_variable cond;
    Mutex mut;
    std::atomic<bool> flag;
};

#endif //DIGIBYTE_THREADINTERRUPT_H
