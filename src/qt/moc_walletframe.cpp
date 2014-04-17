/****************************************************************************
** Meta object code from reading C++ file 'walletframe.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "walletframe.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'walletframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WalletFrame[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      32,   12,   12,   12, 0x0a,
      50,   12,   12,   12, 0x0a,
      78,   73,   12,   12, 0x0a,
     105,   12,   12,   12, 0x2a,
     125,   73,   12,   12, 0x0a,
     153,   12,   12,   12, 0x2a,
     174,   73,   12,   12, 0x0a,
     204,   12,   12,   12, 0x2a,
     234,  227,   12,   12, 0x0a,
     254,   12,   12,   12, 0x0a,
     269,   12,   12,   12, 0x0a,
     288,   12,   12,   12, 0x0a,
     303,   12,   12,   12, 0x0a,
     326,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WalletFrame[] = {
    "WalletFrame\0\0gotoOverviewPage()\0"
    "gotoHistoryPage()\0gotoReceiveCoinsPage()\0"
    "addr\0gotoSendCoinsPage(QString)\0"
    "gotoSendCoinsPage()\0gotoSignMessageTab(QString)\0"
    "gotoSignMessageTab()\0gotoVerifyMessageTab(QString)\0"
    "gotoVerifyMessageTab()\0status\0"
    "encryptWallet(bool)\0backupWallet()\0"
    "changePassphrase()\0unlockWallet()\0"
    "usedSendingAddresses()\0usedReceivingAddresses()\0"
};

void WalletFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WalletFrame *_t = static_cast<WalletFrame *>(_o);
        switch (_id) {
        case 0: _t->gotoOverviewPage(); break;
        case 1: _t->gotoHistoryPage(); break;
        case 2: _t->gotoReceiveCoinsPage(); break;
        case 3: _t->gotoSendCoinsPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->gotoSendCoinsPage(); break;
        case 5: _t->gotoSignMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->gotoSignMessageTab(); break;
        case 7: _t->gotoVerifyMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->gotoVerifyMessageTab(); break;
        case 9: _t->encryptWallet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->backupWallet(); break;
        case 11: _t->changePassphrase(); break;
        case 12: _t->unlockWallet(); break;
        case 13: _t->usedSendingAddresses(); break;
        case 14: _t->usedReceivingAddresses(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WalletFrame::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WalletFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_WalletFrame,
      qt_meta_data_WalletFrame, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WalletFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WalletFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WalletFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WalletFrame))
        return static_cast<void*>(const_cast< WalletFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int WalletFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
