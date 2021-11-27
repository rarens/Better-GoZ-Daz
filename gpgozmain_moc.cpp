/****************************************************************************
** Meta object code from reading C++ file 'gpgozmain.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gpgozmain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpgozmain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BetterGoZExportAction[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_BetterGoZExportAction[] = {
    "BetterGoZExportAction\0"
};

void BetterGoZExportAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData BetterGoZExportAction::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BetterGoZExportAction::staticMetaObject = {
    { &DzEditAction::staticMetaObject, qt_meta_stringdata_BetterGoZExportAction,
      qt_meta_data_BetterGoZExportAction, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BetterGoZExportAction::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BetterGoZExportAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BetterGoZExportAction::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BetterGoZExportAction))
        return static_cast<void*>(const_cast< BetterGoZExportAction*>(this));
    return DzEditAction::qt_metacast(_clname);
}

int BetterGoZExportAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DzEditAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_GpBetterGoZ[] = {

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
      13,   12,   12,   12, 0x0a,
      33,   27,   12,   12, 0x0a,
      60,   56,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GpBetterGoZ[] = {
    "GpBetterGoZ\0\0checkStatus()\0shape\0"
    "onMesh(DzFacetMeshPtr)\0vis\0"
    "dialogVisChanged(bool)\0"
};

void GpBetterGoZ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GpBetterGoZ *_t = static_cast<GpBetterGoZ *>(_o);
        switch (_id) {
        case 0: _t->checkStatus(); break;
        case 1: _t->onMesh((*reinterpret_cast< DzFacetMeshPtr(*)>(_a[1]))); break;
        case 2: _t->dialogVisChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GpBetterGoZ::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GpBetterGoZ::staticMetaObject = {
    { &DzPlugin::staticMetaObject, qt_meta_stringdata_GpBetterGoZ,
      qt_meta_data_GpBetterGoZ, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GpBetterGoZ::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GpBetterGoZ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GpBetterGoZ::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GpBetterGoZ))
        return static_cast<void*>(const_cast< GpBetterGoZ*>(this));
    return DzPlugin::qt_metacast(_clname);
}

int GpBetterGoZ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DzPlugin::qt_metacall(_c, _id, _a);
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
