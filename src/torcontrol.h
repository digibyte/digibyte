<<<<<<< HEAD
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
=======
// Copyright (c) 2015-2019 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for communicating with Tor.
 */
#ifndef DIGIBYTE_TORCONTROL_H
#define DIGIBYTE_TORCONTROL_H

#include <string>

class CService;

extern const std::string DEFAULT_TOR_CONTROL;
static const bool DEFAULT_LISTEN_ONION = true;

void StartTorControl(CService onion_service_target);
void InterruptTorControl();
void StopTorControl();

<<<<<<< HEAD
=======
CService DefaultOnionServiceTarget();

>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
#endif /* DIGIBYTE_TORCONTROL_H */
