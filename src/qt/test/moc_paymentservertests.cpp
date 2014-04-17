/****************************************************************************
** Meta object code from reading C++ file 'paymentservertests.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "paymentservertests.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paymentservertests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PaymentServerTests[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PaymentServerTests[] = {
    "PaymentServerTests\0\0paymentServerTests()\0"
};

void PaymentServerTests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PaymentServerTests *_t = static_cast<PaymentServerTests *>(_o);
        switch (_id) {
        case 0: _t->paymentServerTests(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PaymentServerTests::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PaymentServerTests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PaymentServerTests,
      qt_meta_data_PaymentServerTests, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PaymentServerTests::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PaymentServerTests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PaymentServerTests::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PaymentServerTests))
        return static_cast<void*>(const_cast< PaymentServerTests*>(this));
    return QObject::qt_metacast(_clname);
}

int PaymentServerTests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_RecipientCatcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RecipientCatcher[] = {
    "RecipientCatcher\0\0r\0"
    "getRecipient(SendCoinsRecipient)\0"
};

void RecipientCatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecipientCatcher *_t = static_cast<RecipientCatcher *>(_o);
        switch (_id) {
        case 0: _t->getRecipient((*reinterpret_cast< SendCoinsRecipient(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RecipientCatcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecipientCatcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RecipientCatcher,
      qt_meta_data_RecipientCatcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecipientCatcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecipientCatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecipientCatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecipientCatcher))
        return static_cast<void*>(const_cast< RecipientCatcher*>(this));
    return QObject::qt_metacast(_clname);
}

int RecipientCatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
