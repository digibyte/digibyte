/****************************************************************************
** Meta object code from reading C++ file 'recentrequeststablemodel.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "recentrequeststablemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recentrequeststablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RecentRequestsTableModel[] = {

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
      39,   26,   25,   25, 0x0a,
      70,   63,   25,   25, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_RecentRequestsTableModel[] = {
    "RecentRequestsTableModel\0\0column,order\0"
    "sort(int,Qt::SortOrder)\0column\0sort(int)\0"
};

void RecentRequestsTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecentRequestsTableModel *_t = static_cast<RecentRequestsTableModel *>(_o);
        switch (_id) {
        case 0: _t->sort((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< Qt::SortOrder(*)>(_a[2]))); break;
        case 1: _t->sort((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RecentRequestsTableModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecentRequestsTableModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_RecentRequestsTableModel,
      qt_meta_data_RecentRequestsTableModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecentRequestsTableModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecentRequestsTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecentRequestsTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecentRequestsTableModel))
        return static_cast<void*>(const_cast< RecentRequestsTableModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int RecentRequestsTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
