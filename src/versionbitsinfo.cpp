// Copyright (c) 2016-2019 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <versionbitsinfo.h>

#include <consensus/params.h>

const struct VBDeploymentInfo VersionBitsDeploymentInfo[Consensus::MAX_VERSION_BITS_DEPLOYMENTS] = {
    {
        /*.name =*/ "testdummy",
        /*.gbt_force =*/ true,
    },
    {
        /*.name =*/ "csv",
        /*.gbt_force =*/ true,
    },
    {
        /*.name =*/ "segwit",
        /*.gbt_force =*/ true,
    },
    {
        /*.name =*/ "nversionbips",
        /*.gbt_force =*/ true,
    },
    {
        /*.name =*/ "reservealgo",
        /*.gbt_force =*/ true,
    },
    {
        /*.name =*/ "odo",
        /*.gbt_force =*/ true,
    },
};
