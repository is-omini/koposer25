/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/interface.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN8SplitterE_t {};
} // unnamed namespace

template <> constexpr inline auto Splitter::qt_create_metaobjectdata<qt_meta_tag_ZN8SplitterE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Splitter"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Splitter, qt_meta_tag_ZN8SplitterE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Splitter::staticMetaObject = { {
    QMetaObject::SuperData::link<QSplitter::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SplitterE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SplitterE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8SplitterE_t>.metaTypes,
    nullptr
} };

void Splitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Splitter *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Splitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Splitter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8SplitterE_t>.strings))
        return static_cast<void*>(this);
    return QSplitter::qt_metacast(_clname);
}

int Splitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN17VerticalBoxLayoutE_t {};
} // unnamed namespace

template <> constexpr inline auto VerticalBoxLayout::qt_create_metaobjectdata<qt_meta_tag_ZN17VerticalBoxLayoutE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "VerticalBoxLayout"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VerticalBoxLayout, qt_meta_tag_ZN17VerticalBoxLayoutE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject VerticalBoxLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QVBoxLayout::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VerticalBoxLayoutE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VerticalBoxLayoutE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17VerticalBoxLayoutE_t>.metaTypes,
    nullptr
} };

void VerticalBoxLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VerticalBoxLayout *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *VerticalBoxLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VerticalBoxLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17VerticalBoxLayoutE_t>.strings))
        return static_cast<void*>(this);
    return QVBoxLayout::qt_metacast(_clname);
}

int VerticalBoxLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVBoxLayout::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN19HorizontalBoxLayoutE_t {};
} // unnamed namespace

template <> constexpr inline auto HorizontalBoxLayout::qt_create_metaobjectdata<qt_meta_tag_ZN19HorizontalBoxLayoutE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "HorizontalBoxLayout"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<HorizontalBoxLayout, qt_meta_tag_ZN19HorizontalBoxLayoutE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject HorizontalBoxLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QHBoxLayout::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19HorizontalBoxLayoutE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19HorizontalBoxLayoutE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19HorizontalBoxLayoutE_t>.metaTypes,
    nullptr
} };

void HorizontalBoxLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<HorizontalBoxLayout *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *HorizontalBoxLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HorizontalBoxLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19HorizontalBoxLayoutE_t>.strings))
        return static_cast<void*>(this);
    return QHBoxLayout::qt_metacast(_clname);
}

int HorizontalBoxLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_tag_ZN6ButtonE_t {};
} // unnamed namespace

template <> constexpr inline auto Button::qt_create_metaobjectdata<qt_meta_tag_ZN6ButtonE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Button"
    };

    QtMocHelpers::UintData qt_methods {
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Button, qt_meta_tag_ZN6ButtonE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Button::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ButtonE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ButtonE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6ButtonE_t>.metaTypes,
    nullptr
} };

void Button::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Button *>(_o);
    (void)_t;
    (void)_c;
    (void)_id;
    (void)_a;
}

const QMetaObject *Button::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Button::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6ButtonE_t>.strings))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int Button::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
