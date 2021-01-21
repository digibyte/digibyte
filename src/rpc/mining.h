// Copyright (c) 2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_RPC_MINING_H
#define DIGIBYTE_RPC_MINING_H

/** Default max iterations to try in RPC generatetodescriptor, generatetoaddress, and generateblock. */
static const uint64_t DEFAULT_MAX_TRIES{1000000};

<<<<<<< HEAD
#include <univalue.h>

/** Generate blocks (mine) */
UniValue generateBlocks(std::shared_ptr<CReserveScript> coinbaseScript, int nGenerate, uint64_t nMaxTries, bool keepScript, int algo);

/** Check bounds on a command line confirm target */
unsigned int ParseConfirmTarget(const UniValue& value);

#endif
=======
#endif // DIGIBYTE_RPC_MINING_H
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
