/****************************************************************************
** Meta object code from reading C++ file 'trafficgraphwidget.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "trafficgraphwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trafficgraphwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TrafficGraphWidget[] = {

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
      20,   19,   19,   19, 0x0a,
      39,   34,   19,   19, 0x0a,
      62,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TrafficGraphWidget[] = {
    "TrafficGraphWidget\0\0updateRates()\0"
    "mins\0setGraphRangeMins(int)\0clear()\0"
};

void TrafficGraphWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TrafficGraphWidget *_t = static_cast<TrafficGraphWidget *>(_o);
        switch (_id) {
        case 0: _t->updateRates(); break;
        case 1: _t->setGraphRangeMins((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->clear(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TrafficGraphWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TrafficGraphWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TrafficGraphWidget,
      qt_meta_data_TrafficGraphWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TrafficGraphWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TrafficGraphWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TrafficGraphWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrafficGraphWidget))
        return static_cast<void*>(const_cast< TrafficGraphWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TrafficGraphWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
