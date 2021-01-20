// Copyright (c) 2009-2010 Satoshi Nakamoto
<<<<<<< HEAD:src/utilmoneystr.h
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
=======
// Copyright (c) 2009-2020 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25:src/util/moneystr.h
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
<<<<<<< HEAD:src/utilmoneystr.h
#ifndef DIGIBYTE_UTILMONEYSTR_H
#define DIGIBYTE_UTILMONEYSTR_H

#include <stdint.h>
#include <string>
=======
#ifndef DIGIBYTE_UTIL_MONEYSTR_H
#define DIGIBYTE_UTIL_MONEYSTR_H
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25:src/util/moneystr.h

#include <amount.h>
#include <attributes.h>

#include <string>

/* Do not use these functions to represent or parse monetary amounts to or from
 * JSON but use AmountFromValue and ValueFromAmount for that.
 */
std::string FormatMoney(const CAmount& n);
/** Parse an amount denoted in full coins. E.g. "0.0034" supplied on the command line. **/
NODISCARD bool ParseMoney(const std::string& str, CAmount& nRet);

<<<<<<< HEAD:src/utilmoneystr.h
#endif // DIGIBYTE_UTILMONEYSTR_H
=======
#endif // DIGIBYTE_UTIL_MONEYSTR_H
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25:src/util/moneystr.h
