// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_POW_H
#define DIGIBYTE_POW_H

#include <consensus/params.h>

#include <stdint.h>

class CBlockHeader;
class CBlockIndex;
class uint256;

#if MEMORY_MAPPING 
	class CBlockIndexProxy;
	typedef CBlockIndexProxy CBlockIndexConstPtr;
#else 
	typedef CBlockIndexConstPtr CBlockIndexConstPtr;
#endif

unsigned int GetNextWorkRequired(CBlockIndexConstPtr pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv1(CBlockIndexConstPtr pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv2(CBlockIndexConstPtr pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv3(CBlockIndexConstPtr pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int GetNextWorkRequiredv4(CBlockIndexConstPtr pindexLast, const CBlockHeader *pblock, const Consensus::Params&, int algo);
unsigned int CalculateNextWorkRequired(CBlockIndexConstPtr pindexLast, int64_t nFirstBlockTime, const Consensus::Params&);

/** Check whether a block hash satisfies the proof-of-work requirement specified by nBits */
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params&);
CBlockIndexConstPtr GetLastBlockIndexForAlgo(CBlockIndexConstPtr pindex, const Consensus::Params&, int algo);
CBlockIndexConstPtr GetAlgo();

#endif // DIGIBYTE_POW_H
