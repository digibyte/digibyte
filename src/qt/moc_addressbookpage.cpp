/****************************************************************************
** Meta object code from reading C++ file 'addressbookpage.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "addressbookpage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addressbookpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddressBookPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   41,   16,   16, 0x0a,
      58,   16,   16,   16, 0x08,
      85,   16,   16,   16, 0x08,
     109,   16,   16,   16, 0x08,
     134,   16,   16,   16, 0x08,
     154,   16,   16,   16, 0x08,
     169,   16,   16,   16, 0x08,
     195,   16,   16,   16, 0x08,
     220,  214,   16,   16, 0x08,
     257,  243,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddressBookPage[] = {
    "AddressBookPage\0\0addr\0sendCoins(QString)\0"
    "retval\0done(int)\0on_deleteAddress_clicked()\0"
    "on_newAddress_clicked()\0"
    "on_copyAddress_clicked()\0onCopyLabelAction()\0"
    "onEditAction()\0on_exportButton_clicked()\0"
    "selectionChanged()\0point\0"
    "contextualMenu(QPoint)\0parent,begin,\0"
    "selectNewAddress(QModelIndex,int,int)\0"
};

void AddressBookPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AddressBookPage *_t = static_cast<AddressBookPage *>(_o);
        switch (_id) {
        case 0: _t->sendCoins((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_deleteAddress_clicked(); break;
        case 3: _t->on_newAddress_clicked(); break;
        case 4: _t->on_copyAddress_clicked(); break;
        case 5: _t->onCopyLabelAction(); break;
        case 6: _t->onEditAction(); break;
        case 7: _t->on_exportButton_clicked(); break;
        case 8: _t->selectionChanged(); break;
        case 9: _t->contextualMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: _t->selectNewAddress((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AddressBookPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AddressBookPage::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddressBookPage,
      qt_meta_data_AddressBookPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AddressBookPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AddressBookPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AddressBookPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddressBookPage))
        return static_cast<void*>(const_cast< AddressBookPage*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddressBookPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AddressBookPage::sendCoins(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
