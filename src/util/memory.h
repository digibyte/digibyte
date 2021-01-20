// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

<<<<<<< HEAD:src/utilmemory.h
#ifndef DIGIBYTE_UTILMEMORY_H
#define DIGIBYTE_UTILMEMORY_H
=======
#ifndef DIGIBYTE_UTIL_MEMORY_H
#define DIGIBYTE_UTIL_MEMORY_H
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25:src/util/memory.h

#include <memory>
#include <utility>

//! Substitute for C++14 std::make_unique.
template <typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif
