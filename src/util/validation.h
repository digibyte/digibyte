// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_UTIL_VALIDATION_H
#define DIGIBYTE_UTIL_VALIDATION_H

#include <string>

class ValidationState;

/** Convert ValidationState to a human-readable message for logging */
std::string FormatStateMessage(const ValidationState &state);

extern const std::string strMessageMagic;

#endif // DIGIBYTE_UTIL_VALIDATION_H
