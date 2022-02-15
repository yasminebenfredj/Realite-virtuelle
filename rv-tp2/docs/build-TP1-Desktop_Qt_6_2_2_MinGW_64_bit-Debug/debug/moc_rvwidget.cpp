/****************************************************************************
** Meta object code from reading C++ file 'rvwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../rv-tp1-yasminebenfredj/rvwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rvwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RVWidget_t {
    const uint offsetsAndSize[26];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_RVWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_RVWidget_t qt_meta_stringdata_RVWidget = {
    {
QT_MOC_LITERAL(0, 8), // "RVWidget"
QT_MOC_LITERAL(9, 6), // "update"
QT_MOC_LITERAL(16, 0), // ""
QT_MOC_LITERAL(17, 14), // "startAnimation"
QT_MOC_LITERAL(32, 9), // "changeFov"
QT_MOC_LITERAL(42, 3), // "fov"
QT_MOC_LITERAL(46, 13), // "changeOpacity"
QT_MOC_LITERAL(60, 10), // "newOpacity"
QT_MOC_LITERAL(71, 11), // "changeSpeed"
QT_MOC_LITERAL(83, 8), // "newSpeed"
QT_MOC_LITERAL(92, 15), // "changeDirection"
QT_MOC_LITERAL(108, 12), // "newDirection"
QT_MOC_LITERAL(121, 13) // "reinitialiser"

    },
    "RVWidget\0update\0\0startAnimation\0"
    "changeFov\0fov\0changeOpacity\0newOpacity\0"
    "changeSpeed\0newSpeed\0changeDirection\0"
    "newDirection\0reinitialiser"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RVWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x08,    1 /* Private */,
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    1,   58,    2, 0x0a,    3 /* Public */,
       6,    1,   61,    2, 0x0a,    5 /* Public */,
       8,    1,   64,    2, 0x0a,    7 /* Public */,
      10,    1,   67,    2, 0x0a,    9 /* Public */,
      12,    0,   70,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,

       0        // eod
};

void RVWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RVWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->startAnimation(); break;
        case 2: _t->changeFov((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->changeOpacity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->changeSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changeDirection((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->reinitialiser(); break;
        default: ;
        }
    }
}

const QMetaObject RVWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_RVWidget.offsetsAndSize,
    qt_meta_data_RVWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_RVWidget_t
, QtPrivate::TypeAndForceComplete<RVWidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *RVWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RVWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RVWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int RVWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
