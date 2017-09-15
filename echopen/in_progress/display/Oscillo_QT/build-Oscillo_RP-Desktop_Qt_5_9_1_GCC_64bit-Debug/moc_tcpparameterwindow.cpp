/****************************************************************************
** Meta object code from reading C++ file 'tcpparameterwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcpparameterwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpparameterwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TcpParameterWindow_t {
    QByteArrayData data[9];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpParameterWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpParameterWindow_t qt_meta_stringdata_TcpParameterWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "TcpParameterWindow"
QT_MOC_LITERAL(1, 19, 13), // "on_connection"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "SOCKET"
QT_MOC_LITERAL(4, 41, 4), // "sock"
QT_MOC_LITERAL(5, 46, 15), // "on_deconnection"
QT_MOC_LITERAL(6, 62, 18), // "on_ramp_connection"
QT_MOC_LITERAL(7, 81, 28), // "on_ButtonDeconnexion_clicked"
QT_MOC_LITERAL(8, 110, 26) // "on_ButtonConnexion_clicked"

    },
    "TcpParameterWindow\0on_connection\0\0"
    "SOCKET\0sock\0on_deconnection\0"
    "on_ramp_connection\0on_ButtonDeconnexion_clicked\0"
    "on_ButtonConnexion_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpParameterWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    1,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   46,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpParameterWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpParameterWindow *_t = static_cast<TcpParameterWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_connection((*reinterpret_cast< SOCKET(*)>(_a[1]))); break;
        case 1: _t->on_deconnection(); break;
        case 2: _t->on_ramp_connection((*reinterpret_cast< SOCKET(*)>(_a[1]))); break;
        case 3: _t->on_ButtonDeconnexion_clicked(); break;
        case 4: _t->on_ButtonConnexion_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpParameterWindow::*_t)(SOCKET );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpParameterWindow::on_connection)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TcpParameterWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpParameterWindow::on_deconnection)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TcpParameterWindow::*_t)(SOCKET );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpParameterWindow::on_ramp_connection)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TcpParameterWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TcpParameterWindow.data,
      qt_meta_data_TcpParameterWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TcpParameterWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpParameterWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TcpParameterWindow.stringdata0))
        return static_cast<void*>(const_cast< TcpParameterWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int TcpParameterWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TcpParameterWindow::on_connection(SOCKET _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpParameterWindow::on_deconnection()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TcpParameterWindow::on_ramp_connection(SOCKET _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
