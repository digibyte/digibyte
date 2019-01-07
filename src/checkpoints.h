// Copyright (c) 2009-2017 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_CHECKPOINTS_H
#define DIGIBYTE_CHECKPOINTS_H

#include <chain.h>
#include <uint256.h>

#include <map>

struct CCheckpointData;

/**
 * Block-chain checkpoints are compiled-in sanity checks.
 * They are updated every release or three.
 */
namespace Checkpoints
{

//! Returns last CBlockIndexPtr that is a checkpoint
CBlockIndexRawPtr GetLastCheckpoint(const CCheckpointData& data);

} //namespace Checkpoints

#endif // DIGIBYTE_CHECKPOINTS_H
