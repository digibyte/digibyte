/****************************************************************************
** Meta object code from reading C++ file 'askpassphrasedialog.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "askpassphrasedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'askpassphrasedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AskPassphraseDialog[] = {

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
      21,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AskPassphraseDialog[] = {
    "AskPassphraseDialog\0\0textChanged()\0"
};

void AskPassphraseDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AskPassphraseDialog *_t = static_cast<AskPassphraseDialog *>(_o);
        switch (_id) {
        case 0: _t->textChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AskPassphraseDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AskPassphraseDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AskPassphraseDialog,
      qt_meta_data_AskPassphraseDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AskPassphraseDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AskPassphraseDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AskPassphraseDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AskPassphraseDialog))
        return static_cast<void*>(const_cast< AskPassphraseDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AskPassphraseDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
