// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2014-2020 The DigiByte Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DIGIBYTE_QT_DIGIBYTEADDRESSVALIDATOR_H
#define DIGIBYTE_QT_DIGIBYTEADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class DigiByteAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DigiByteAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** DigiByte address widget validator, checks for a valid digibyte address.
 */
class DigiByteAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DigiByteAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // DIGIBYTE_QT_DIGIBYTEADDRESSVALIDATOR_H
