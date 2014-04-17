/****************************************************************************
** Meta object code from reading C++ file 'paymentserver.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "paymentserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paymentserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PaymentServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      72,   58,   14,   14, 0x05,
     120,  100,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     150,   14,   14,   14, 0x0a,
     189,  160,   14,   14, 0x0a,
     247,  245,   14,   14, 0x0a,
     272,   14,   14,   14, 0x08,
     294,   14,   14,   14, 0x08,
     331,  329,   14,   14, 0x08,
     380,   58,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PaymentServer[] = {
    "PaymentServer\0\0"
    "receivedPaymentRequest(SendCoinsRecipient)\0"
    "paymentACKMsg\0receivedPaymentACK(QString)\0"
    "title,message,style\0message(QString,QString,uint)\0"
    "uiReady()\0wallet,recipient,transaction\0"
    "fetchPaymentACK(CWallet*,SendCoinsRecipient,QByteArray)\0"
    "s\0handleURIOrFile(QString)\0"
    "handleURIConnection()\0"
    "netRequestFinished(QNetworkReply*)\0,\0"
    "reportSslErrors(QNetworkReply*,QList<QSslError>)\0"
    "handlePaymentACK(QString)\0"
};

void PaymentServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PaymentServer *_t = static_cast<PaymentServer *>(_o);
        switch (_id) {
        case 0: _t->receivedPaymentRequest((*reinterpret_cast< SendCoinsRecipient(*)>(_a[1]))); break;
        case 1: _t->receivedPaymentACK((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->message((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 3: _t->uiReady(); break;
        case 4: _t->fetchPaymentACK((*reinterpret_cast< CWallet*(*)>(_a[1])),(*reinterpret_cast< SendCoinsRecipient(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 5: _t->handleURIOrFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->handleURIConnection(); break;
        case 7: _t->netRequestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->reportSslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        case 9: _t->handlePaymentACK((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PaymentServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PaymentServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PaymentServer,
      qt_meta_data_PaymentServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PaymentServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PaymentServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PaymentServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PaymentServer))
        return static_cast<void*>(const_cast< PaymentServer*>(this));
    return QObject::qt_metacast(_clname);
}

int PaymentServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PaymentServer::receivedPaymentRequest(SendCoinsRecipient _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PaymentServer::receivedPaymentACK(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PaymentServer::message(const QString & _t1, const QString & _t2, unsigned int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
