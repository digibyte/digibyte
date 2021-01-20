<<<<<<< HEAD
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Copyright (c) 2014-2019 The DigiByte Core developers
=======
// Copyright (c) 2017-2019 The DigiByte Core developers
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_WALLETINITINTERFACE_H
#define DIGIBYTE_WALLETINITINTERFACE_H

class ArgsManager;

struct NodeContext;

class WalletInitInterface {
public:
    /** Is the wallet component enabled */
    virtual bool HasWalletSupport() const = 0;
    /** Get wallet help string */
    virtual void AddWalletOptions(ArgsManager& argsman) const = 0;
    /** Check wallet parameter interaction */
    virtual bool ParameterInteraction() const = 0;
    /** Add wallets that should be opened to list of chain clients. */
    virtual void Construct(NodeContext& node) const = 0;

    virtual ~WalletInitInterface() {}
};

<<<<<<< HEAD
=======
extern const WalletInitInterface& g_wallet_init_interface;

>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
#endif // DIGIBYTE_WALLETINITINTERFACE_H
