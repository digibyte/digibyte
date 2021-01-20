// Copyright (c) 2011-2014 The DigiByte Core developers
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

<<<<<<< HEAD
    State validate(QString &input, int &pos) const;
=======
    State validate(QString &input, int &pos) const override;
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
};

/** DigiByte address widget validator, checks for a valid digibyte address.
 */
class DigiByteAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit DigiByteAddressCheckValidator(QObject *parent);

<<<<<<< HEAD
    State validate(QString &input, int &pos) const;
=======
    State validate(QString &input, int &pos) const override;
>>>>>>> 5358de127d898d4bb197e4d8dc2db4113391bb25
};

#endif // DIGIBYTE_QT_DIGIBYTEADDRESSVALIDATOR_H
