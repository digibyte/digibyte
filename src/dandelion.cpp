// Copyright (c) 2021 The Digibyte developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
#include <config/digibyte-config.h>
#endif

#include <net.h>
#include <shutdown.h>

extern bool g_ibd_complete;

bool CConnman::isDandelionInbound(const CNode* const pnode) const
{
    return (std::find(vDandelionInbound.begin(), vDandelionInbound.end(), pnode) != vDandelionInbound.end());
}

bool CConnman::isLocalDandelionDestinationSet() const
{
    return (localDandelionDestination != nullptr);
}

bool CConnman::setLocalDandelionDestination()
{
    if (!isLocalDandelionDestinationSet()) {
        localDandelionDestination = SelectFromDandelionDestinations();
        LogPrint(BCLog::DANDELION, "Set local Dandelion destination:\n%s", GetDandelionRoutingDataDebugString());
    }
    return isLocalDandelionDestinationSet();
}

CNode* CConnman::getDandelionDestination(CNode* pfrom)
{
    for (auto const& e : mDandelionRoutes) {
        if (pfrom == e.first) {
            return e.second;
        }
    }
    CNode* newPto = SelectFromDandelionDestinations();
    if (newPto != nullptr) {
        mDandelionRoutes.insert(std::make_pair(pfrom, newPto));
        LogPrint(BCLog::DANDELION, "Added Dandelion route:\n%s", GetDandelionRoutingDataDebugString());
    }
    return newPto;
}

bool CConnman::localDandelionDestinationPushInventory(const CInv& inv)
{
    if (isLocalDandelionDestinationSet()) {
        localDandelionDestination->PushOtherInventory(inv);
        return true;
    } else if (setLocalDandelionDestination()) {
        localDandelionDestination->PushOtherInventory(inv);
        return true;
    } else {
        return false;
    }
}

bool CConnman::insertDandelionEmbargo(const uint256& hash, std::chrono::microseconds& embargo) {
    auto pair = mDandelionEmbargo.insert(std::make_pair(hash, embargo));
    return pair.second;
}

bool CConnman::isTxDandelionEmbargoed(const uint256& hash) const
{
    auto pair = mDandelionEmbargo.find(hash);
    if (pair != mDandelionEmbargo.end()) {
        return true;
    } else {
        return false;
    }
}

bool CConnman::removeDandelionEmbargo(const uint256& hash)
{
    bool removed = false;
    for (auto iter = mDandelionEmbargo.begin(); iter != mDandelionEmbargo.end();) {
        if (iter->first == hash) {
            iter = mDandelionEmbargo.erase(iter);
            removed = true;
        } else {
            iter++;
        }
    }
    return removed;
}

CNode* CConnman::SelectFromDandelionDestinations() const
{
    std::map<CNode*, uint64_t> mDandelionDestinationCounts;
    for (size_t i = 0; i < vDandelionDestination.size(); i++) {
        mDandelionDestinationCounts.insert(std::make_pair(vDandelionDestination.at(i), 0));
    }
    for (auto& e : mDandelionDestinationCounts) {
        for (auto const& f : mDandelionRoutes) {
            if (e.first == f.second) {
                e.second += 1;
            }
        }
    }
    unsigned int minNumConnections = vDandelionInbound.size();
    for (auto const& e : mDandelionDestinationCounts) {
        if (e.second < minNumConnections) {
            minNumConnections = e.second;
        }
    }
    std::vector<CNode*> candidateDestinations;
    for (auto const& e : mDandelionDestinationCounts) {
        if (e.second == minNumConnections) {
            candidateDestinations.push_back(e.first);
        }
    }
    FastRandomContext rng;
    CNode* dandelionDestination = nullptr;
    if (candidateDestinations.size() > 0) {
        dandelionDestination = candidateDestinations.at(rng.randrange(candidateDestinations.size()));
    }
    return dandelionDestination;
}

void CConnman::CloseDandelionConnections(const CNode* const pnode)
{
    // Remove pnode from vDandelionInbound, if present
    for (auto iter = vDandelionInbound.begin(); iter != vDandelionInbound.end();) {
        if (*iter == pnode) {
            iter = vDandelionInbound.erase(iter);
        } else {
            iter++;
        }
    }
    // Remove pnode from vDandelionOutbound, if present
    for (auto iter = vDandelionOutbound.begin(); iter != vDandelionOutbound.end();) {
        if (*iter == pnode) {
            iter = vDandelionOutbound.erase(iter);
        } else {
            iter++;
        }
    }
    // Remove pnode from vDandelionDestination, if present
    bool isDandelionDestination = false;
    for (auto iter = vDandelionDestination.begin(); iter != vDandelionDestination.end();) {
        if (*iter == pnode) {
            isDandelionDestination = true;
            iter = vDandelionDestination.erase(iter);
        } else {
            iter++;
        }
    }
    // Generate a replacement Dandelion destination, if necessary
    if (isDandelionDestination) {
        // Gather a vector of candidate replacements (outbound peers that are not already destinations)
        std::vector<CNode*> candidateReplacements;
        for (auto iteri = vDandelionOutbound.begin(); iteri != vDandelionOutbound.end();) {
            bool eligibleCandidate = true;
            for (auto iterj = vDandelionDestination.begin(); iterj != vDandelionDestination.end();) {
                if (*iteri == *iterj) {
                    eligibleCandidate = false;
                    iterj = vDandelionDestination.end();
                } else {
                    iterj++;
                }
            }
            if (eligibleCandidate) {
                candidateReplacements.push_back(*iteri);
            }
            iteri++;
        }
        // Select a candidate to be the replacement destination
        FastRandomContext rng;
        CNode* replacementDestination = nullptr;
        if (candidateReplacements.size() > 0) {
            replacementDestination = candidateReplacements.at(rng.randrange(candidateReplacements.size()));
        }
        if (replacementDestination != nullptr) {
            vDandelionDestination.push_back(replacementDestination);
        }
    }
    // Generate a replacement pnode, to be used if necessary
    CNode* newPto = SelectFromDandelionDestinations();
    // Remove from mDandelionRoutes, if present; if destination, try to replace
    for (auto iter = mDandelionRoutes.begin(); iter != mDandelionRoutes.end();) {
        if (iter->first == pnode) {
            iter = mDandelionRoutes.erase(iter);
        } else if (iter->second == pnode) {
            if (newPto == nullptr) {
                iter = mDandelionRoutes.erase(iter);
            } else {
                iter->second = newPto;
                iter++;
            }
        } else {
            iter++;
        }
    }
    // Replace localDandelionDestination if equal to pnode
    if (localDandelionDestination == pnode) {
        localDandelionDestination = newPto;
    }
}

std::string CConnman::GetDandelionRoutingDataDebugString() const
{
    std::string dandelionRoutingDataDebugString = "";
    dandelionRoutingDataDebugString.append("  vDandelionInbound: ");
    for (auto const& e : vDandelionInbound) {
        dandelionRoutingDataDebugString.append(std::to_string(e->GetId()) + " ");
    }
    dandelionRoutingDataDebugString.append("\n  vDandelionOutbound: ");
    for (auto const& e : vDandelionOutbound) {
        dandelionRoutingDataDebugString.append(std::to_string(e->GetId()) + " ");
    }
    dandelionRoutingDataDebugString.append("\n  vDandelionDestination: ");
    for (auto const& e : vDandelionDestination) {
        dandelionRoutingDataDebugString.append(std::to_string(e->GetId()) + " ");
    }
    dandelionRoutingDataDebugString.append("\n  mDandelionRoutes: ");
    for (auto const& e : mDandelionRoutes) {
        dandelionRoutingDataDebugString.append("(" + std::to_string(e.first->GetId()) + "," + std::to_string(e.second->GetId()) + ") ");
    }
    dandelionRoutingDataDebugString.append("\n  localDandelionDestination: ");
    if (!localDandelionDestination) {
        dandelionRoutingDataDebugString.append("nullptr");
    } else {
        dandelionRoutingDataDebugString.append(std::to_string(localDandelionDestination->GetId()));
    }
    dandelionRoutingDataDebugString.append("\n");
    return dandelionRoutingDataDebugString;
}

void CConnman::DandelionShuffle()
{
    // Dandelion debug message
    LogPrint(BCLog::DANDELION, "Before Dandelion shuffle:\n%s", GetDandelionRoutingDataDebugString());
    {
        // Lock node pointers
        LOCK(cs_vNodes);
        // Iterate through mDandelionRoutes to facilitate bookkeeping
        for (auto iter = mDandelionRoutes.begin(); iter != mDandelionRoutes.end();) {
            iter = mDandelionRoutes.erase(iter);
        }
        // Set localDandelionDestination to nulltpr and perform bookkeeping
        if (localDandelionDestination != nullptr) {
            localDandelionDestination = nullptr;
        }
        // Clear vDandelionDestination
        //  (bookkeeping already done while iterating through mDandelionRoutes)
        vDandelionDestination.clear();
        // Repopulate vDandelionDestination
        while (vDandelionDestination.size() < DANDELION_MAX_DESTINATIONS && vDandelionDestination.size() < vDandelionOutbound.size()) {
            std::vector<CNode*> candidateDestinations;
            for (auto iteri = vDandelionOutbound.begin(); iteri != vDandelionOutbound.end();) {
                bool eligibleCandidate = true;
                for (auto iterj = vDandelionDestination.begin(); iterj != vDandelionDestination.end();) {
                    if (*iteri == *iterj) {
                        eligibleCandidate = false;
                        iterj = vDandelionDestination.end();
                    } else {
                        iterj++;
                    }
                }
                if (eligibleCandidate) {
                    candidateDestinations.push_back(*iteri);
                }
                iteri++;
            }
            FastRandomContext rng;
            if (candidateDestinations.size() > 0) {
                vDandelionDestination.push_back(candidateDestinations.at(rng.randrange(candidateDestinations.size())));
            } else {
                break;
            }
        }
        // Generate new routes
        for (auto pnode : vDandelionInbound) {
            CNode* pto = SelectFromDandelionDestinations();
            if (pto) {
                mDandelionRoutes.insert(std::make_pair(pnode, pto));
            }
        }
        localDandelionDestination = SelectFromDandelionDestinations();
    }
    // Dandelion debug message
    LogPrint(BCLog::DANDELION, "After Dandelion shuffle:\n%s", GetDandelionRoutingDataDebugString());
}

void CConnman::ThreadDandelionShuffle()
{
    while (!ShutdownRequested()) {
        UninterruptibleSleep(std::chrono::milliseconds{1000});
        if (g_ibd_complete) {
           break;
        }
        if(ShutdownRequested()) {
           return;
        }
    }

    auto now = GetTime<std::chrono::microseconds>();
    auto nNextDandelionShuffle = PoissonNextSend(now, DANDELION_SHUFFLE_INTERVAL);

    while (!ShutdownRequested()) {
        now = GetTime<std::chrono::milliseconds>();
        if (now > nNextDandelionShuffle) {
            DandelionShuffle();
            nNextDandelionShuffle = PoissonNextSend(now, DANDELION_SHUFFLE_INTERVAL);
        }
        if (ShutdownRequested()) {
            return;
        }
        if (!interruptNet.sleep_for(std::chrono::milliseconds(100))) {
            return;
        }
    }
}
