/****************************************************************************
** Meta object code from reading C++ file 'betterGozDlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "betterGozDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'betterGozDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BetterGoZDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   17,   16,   16, 0x0a,
      48,   16,   16,   16, 0x0a,
      66,   16,   16,   16, 0x0a,
      82,   80,   16,   16, 0x0a,
     112,   97,   16,   16, 0x0a,
     147,  145,   16,   16, 0x2a,
     175,   16,   16,   16, 0x0a,
     188,   16,   16,   16, 0x0a,
     202,   16,   16,   16, 0x0a,
     217,   16,   16,   16, 0x0a,
     233,  229,  224,   16, 0x0a,
     277,  259,  255,   16, 0x0a,
     316,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BetterGoZDialog[] = {
    "BetterGoZDialog\0\0node\0selectionChanged(DzNode*)\0"
    "updateMorphName()\0createMorph()\0s\0"
    "print(QString)\0,,fromSelected\0"
    "updatePath(DzNode*,QString,bool)\0,\0"
    "updatePath(DzNode*,QString)\0addNewPath()\0"
    "importAsNew()\0postLoadMesh()\0show()\0"
    "bool\0dst\0doGraftMorph(DzNode*)\0int\0"
    "subDMesh,baseMesh\0"
    "calcSubdLev(DzFacetMesh*,DzFacetMesh*)\0"
    "hideEvent(QHideEvent*)\0"
};

void BetterGoZDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BetterGoZDialog *_t = static_cast<BetterGoZDialog *>(_o);
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< DzNode*(*)>(_a[1]))); break;
        case 1: _t->updateMorphName(); break;
        case 2: _t->createMorph(); break;
        case 3: _t->print((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->updatePath((*reinterpret_cast< DzNode*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 5: _t->updatePath((*reinterpret_cast< DzNode*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->addNewPath(); break;
        case 7: _t->importAsNew(); break;
        case 8: _t->postLoadMesh(); break;
        case 9: _t->show(); break;
        case 10: { bool _r = _t->doGraftMorph((*reinterpret_cast< DzNode*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { int _r = _t->calcSubdLev((*reinterpret_cast< DzFacetMesh*(*)>(_a[1])),(*reinterpret_cast< DzFacetMesh*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 12: _t->hideEvent((*reinterpret_cast< QHideEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BetterGoZDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BetterGoZDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BetterGoZDialog,
      qt_meta_data_BetterGoZDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BetterGoZDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BetterGoZDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BetterGoZDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BetterGoZDialog))
        return static_cast<void*>(const_cast< BetterGoZDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int BetterGoZDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
