/****************************************************************************
** Meta object code from reading C++ file 'receiverequestdialog.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "receiverequestdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiverequestdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRImageWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      27,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QRImageWidget[] = {
    "QRImageWidget\0\0saveImage()\0copyImage()\0"
};

void QRImageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRImageWidget *_t = static_cast<QRImageWidget *>(_o);
        switch (_id) {
        case 0: _t->saveImage(); break;
        case 1: _t->copyImage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QRImageWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRImageWidget::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QRImageWidget,
      qt_meta_data_QRImageWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRImageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRImageWidget))
        return static_cast<void*>(const_cast< QRImageWidget*>(this));
    return QLabel::qt_metacast(_clname);
}

int QRImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_ReceiveRequestDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   21,   21,   21, 0x08,
      46,   21,   21,   21, 0x08,
      74,   21,   21,   21, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ReceiveRequestDialog[] = {
    "ReceiveRequestDialog\0\0on_btnCopyURI_clicked()\0"
    "on_btnCopyAddress_clicked()\0update()\0"
};

void ReceiveRequestDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReceiveRequestDialog *_t = static_cast<ReceiveRequestDialog *>(_o);
        switch (_id) {
        case 0: _t->on_btnCopyURI_clicked(); break;
        case 1: _t->on_btnCopyAddress_clicked(); break;
        case 2: _t->update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ReceiveRequestDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReceiveRequestDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ReceiveRequestDialog,
      qt_meta_data_ReceiveRequestDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReceiveRequestDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReceiveRequestDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReceiveRequestDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReceiveRequestDialog))
        return static_cast<void*>(const_cast< ReceiveRequestDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ReceiveRequestDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
