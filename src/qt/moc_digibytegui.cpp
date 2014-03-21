/****************************************************************************
** Meta object code from reading C++ file 'digibytegui.h'
**
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "digibytegui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'digibytegui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DigiByteGUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   37,   11,   11, 0x0a,
      85,   66,   11,   11, 0x0a,
     131,  107,   11,   11, 0x0a,
     187,  167,   11,   11, 0x2a,
     224,  217,   11,   11, 0x0a,
     264,  254,  249,   11, 0x0a,
     335,  305,   11,   11, 0x0a,
     391,   11,   11,   11, 0x08,
     410,   11,   11,   11, 0x08,
     428,   11,   11,   11, 0x08,
     456,  451,   11,   11, 0x08,
     483,   11,   11,   11, 0x28,
     503,  451,   11,   11, 0x08,
     531,   11,   11,   11, 0x28,
     552,  451,   11,   11, 0x08,
     582,   11,   11,   11, 0x28,
     605,   11,   11,   11, 0x08,
     619,   11,   11,   11, 0x08,
     636,   11,   11,   11, 0x08,
     651,   11,   11,   11, 0x08,
     683,  676,   11,   11, 0x08,
     750,  736,   11,   11, 0x08,
     778,   11,   11,   11, 0x28,
     802,   11,   11,   11, 0x08,
     817,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DigiByteGUI[] = {
    "DigiByteGUI\0\0uri\0receivedURI(QString)\0"
    "count\0setNumConnections(int)\0"
    "count,nTotalBlocks\0setNumBlocks(int,int)\0"
    "title,message,style,ret\0"
    "message(QString,QString,uint,bool*)\0"
    "title,message,style\0message(QString,QString,uint)\0"
    "status\0setEncryptionStatus(int)\0bool\0"
    "recipient\0handlePaymentRequest(SendCoinsRecipient)\0"
    "date,unit,amount,type,address\0"
    "incomingTransaction(QString,int,qint64,QString,QString)\0"
    "gotoOverviewPage()\0gotoHistoryPage()\0"
    "gotoReceiveCoinsPage()\0addr\0"
    "gotoSendCoinsPage(QString)\0"
    "gotoSendCoinsPage()\0gotoSignMessageTab(QString)\0"
    "gotoSignMessageTab()\0gotoVerifyMessageTab(QString)\0"
    "gotoVerifyMessageTab()\0openClicked()\0"
    "optionsClicked()\0aboutClicked()\0"
    "showHelpMessageClicked()\0reason\0"
    "trayIconActivated(QSystemTrayIcon::ActivationReason)\0"
    "fToggleHidden\0showNormalIfMinimized(bool)\0"
    "showNormalIfMinimized()\0toggleHidden()\0"
    "detectShutdown()\0"
};

void DigiByteGUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DigiByteGUI *_t = static_cast<DigiByteGUI *>(_o);
        switch (_id) {
        case 0: _t->receivedURI((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setNumConnections((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setNumBlocks((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->message((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])),(*reinterpret_cast< bool*(*)>(_a[4]))); break;
        case 4: _t->message((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 5: _t->setEncryptionStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: { bool _r = _t->handlePaymentRequest((*reinterpret_cast< const SendCoinsRecipient(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->incomingTransaction((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 8: _t->gotoOverviewPage(); break;
        case 9: _t->gotoHistoryPage(); break;
        case 10: _t->gotoReceiveCoinsPage(); break;
        case 11: _t->gotoSendCoinsPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->gotoSendCoinsPage(); break;
        case 13: _t->gotoSignMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->gotoSignMessageTab(); break;
        case 15: _t->gotoVerifyMessageTab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->gotoVerifyMessageTab(); break;
        case 17: _t->openClicked(); break;
        case 18: _t->optionsClicked(); break;
        case 19: _t->aboutClicked(); break;
        case 20: _t->showHelpMessageClicked(); break;
        case 21: _t->trayIconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 22: _t->showNormalIfMinimized((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->showNormalIfMinimized(); break;
        case 24: _t->toggleHidden(); break;
        case 25: _t->detectShutdown(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DigiByteGUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DigiByteGUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DigiByteGUI,
      qt_meta_data_DigiByteGUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DigiByteGUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DigiByteGUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DigiByteGUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DigiByteGUI))
        return static_cast<void*>(const_cast< DigiByteGUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DigiByteGUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void DigiByteGUI::receivedURI(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
