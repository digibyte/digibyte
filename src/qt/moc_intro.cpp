/****************************************************************************
** Meta object code from reading C++ file 'intro.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "intro.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'intro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Intro[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,
      22,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   35,    6,    6, 0x0a,
     101,   96,    6,    6, 0x08,
     139,    6,    6,    6, 0x08,
     167,    6,    6,    6, 0x08,
     195,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Intro[] = {
    "Intro\0\0requestCheck()\0stopThread()\0"
    "status,message,bytesAvailable\0"
    "setStatus(int,QString,quint64)\0arg1\0"
    "on_dataDirectory_textChanged(QString)\0"
    "on_ellipsisButton_clicked()\0"
    "on_dataDirDefault_clicked()\0"
    "on_dataDirCustom_clicked()\0"
};

void Intro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Intro *_t = static_cast<Intro *>(_o);
        switch (_id) {
        case 0: _t->requestCheck(); break;
        case 1: _t->stopThread(); break;
        case 2: _t->setStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3]))); break;
        case 3: _t->on_dataDirectory_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->on_ellipsisButton_clicked(); break;
        case 5: _t->on_dataDirDefault_clicked(); break;
        case 6: _t->on_dataDirCustom_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Intro::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Intro::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Intro,
      qt_meta_data_Intro, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Intro::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Intro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Intro::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Intro))
        return static_cast<void*>(const_cast< Intro*>(this));
    return QDialog::qt_metacast(_clname);
}

int Intro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Intro::requestCheck()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Intro::stopThread()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
