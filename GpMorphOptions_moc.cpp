/****************************************************************************
** Meta object code from reading C++ file 'GpMorphOptions.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GpMorphOptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GpMorphOptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GpMorphOptions[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   16,   15, 0x0a,
      41,   15,   33,   15, 0x0a,
      79,   15,   52,   15, 0x0a,
      93,   15,   33,   15, 0x0a,
     113,   15,  108,   15, 0x0a,
     121,   15,  108,   15, 0x0a,
     129,   15,  108,   15, 0x0a,
     139,   15,  108,   15, 0x0a,
     151,   15,   33,   15, 0x0a,
     174,   15,  161,   15, 0x0a,
     208,   15,  184,   15, 0x0a,
     222,   15,   33,   15, 0x0a,
     237,   15,   15,   15, 0x0a,
     262,   15,   15,   15, 0x0a,
     287,   15,  161,   15, 0x0a,
     315,   15,  303,   15, 0x0a,
     337,  332,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GpMorphOptions[] = {
    "GpMorphOptions\0\0int\0getSubDLev()\0"
    "QString\0toString()\0DzMorphLoader::SubdMapping\0"
    "getSubDCage()\0getMorphName()\0bool\0"
    "getAG()\0getOE()\0getRevD()\0getMirror()\0"
    "getPath()\0DzFacetMesh*\0getMesh()\0"
    "DzMorphLoader::LoadMode\0getLoadMode()\0"
    "toJsonString()\0setOptionsFromSettings()\0"
    "writeOptionsToSettings()\0getScaledMesh()\0"
    "QStringList\0getNameHistory()\0mesh\0"
    "setMesh(DzFacetMeshPtr)\0"
};

void GpMorphOptions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GpMorphOptions *_t = static_cast<GpMorphOptions *>(_o);
        switch (_id) {
        case 0: { int _r = _t->getSubDLev();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->toString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { DzMorphLoader::SubdMapping _r = _t->getSubDCage();
            if (_a[0]) *reinterpret_cast< DzMorphLoader::SubdMapping*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getMorphName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->getAG();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->getOE();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->getRevD();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->getMirror();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->getPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { DzFacetMesh* _r = _t->getMesh();
            if (_a[0]) *reinterpret_cast< DzFacetMesh**>(_a[0]) = _r; }  break;
        case 10: { DzMorphLoader::LoadMode _r = _t->getLoadMode();
            if (_a[0]) *reinterpret_cast< DzMorphLoader::LoadMode*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->toJsonString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: _t->setOptionsFromSettings(); break;
        case 13: _t->writeOptionsToSettings(); break;
        case 14: { DzFacetMesh* _r = _t->getScaledMesh();
            if (_a[0]) *reinterpret_cast< DzFacetMesh**>(_a[0]) = _r; }  break;
        case 15: { QStringList _r = _t->getNameHistory();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 16: _t->setMesh((*reinterpret_cast< DzFacetMeshPtr(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GpMorphOptions::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GpMorphOptions::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GpMorphOptions,
      qt_meta_data_GpMorphOptions, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GpMorphOptions::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GpMorphOptions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GpMorphOptions::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GpMorphOptions))
        return static_cast<void*>(const_cast< GpMorphOptions*>(this));
    return QObject::qt_metacast(_clname);
}

int GpMorphOptions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
