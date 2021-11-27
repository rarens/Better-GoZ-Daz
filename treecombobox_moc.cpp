/****************************************************************************
** Meta object code from reading C++ file 'treecombobox.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "treecombobox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treecombobox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeComboBox[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   13,   14,   13, 0x0a,
      42,   36,   13,   13, 0x0a,
      85,   72,   67,   13, 0x0a,
     119,  115,   13,   13, 0x0a,
     149,   13,   13,   13, 0x0a,
     179,  169,   13,   13, 0x0a,
     207,   13,   13,   13, 0x0a,
     219,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TreeComboBox[] = {
    "TreeComboBox\0\0QString\0getFullPath()\0"
    "event\0paintEvent(QPaintEvent*)\0bool\0"
    "object,event\0eventFilter(QObject*,QEvent*)\0"
    "idx\0updateModelIndex(QModelIndex)\0"
    "updateComboString()\0node,path\0"
    "updatePath(DzNode*,QString)\0showPopup()\0"
    "hidePopup()\0"
};

void TreeComboBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TreeComboBox *_t = static_cast<TreeComboBox *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->getFullPath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        case 2: { bool _r = _t->eventFilter((*reinterpret_cast< QObject*(*)>(_a[1])),(*reinterpret_cast< QEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: _t->updateModelIndex((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->updateComboString(); break;
        case 5: _t->updatePath((*reinterpret_cast< DzNode*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->showPopup(); break;
        case 7: _t->hidePopup(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TreeComboBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TreeComboBox::staticMetaObject = {
    { &QComboBox::staticMetaObject, qt_meta_stringdata_TreeComboBox,
      qt_meta_data_TreeComboBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeComboBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeComboBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeComboBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeComboBox))
        return static_cast<void*>(const_cast< TreeComboBox*>(this));
    return QComboBox::qt_metacast(_clname);
}

int TreeComboBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QComboBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
