/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DBMS/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "on_open_triggered"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 21), // "on_addtable_triggered"
QT_MOC_LITERAL(4, 52, 22), // "on_findtable_triggered"
QT_MOC_LITERAL(5, 75, 21), // "on_backbutton_clicked"
QT_MOC_LITERAL(6, 97, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 119, 22), // "on_clearbutton_clicked"
QT_MOC_LITERAL(8, 142, 12), // "on_readtable"
QT_MOC_LITERAL(9, 155, 19), // "on_readdb_triggered"
QT_MOC_LITERAL(10, 175, 34), // "on_treeWidget_itemSelectionCh..."
QT_MOC_LITERAL(11, 210, 3), // "png"
QT_MOC_LITERAL(12, 214, 19), // "on_trefresh_clicked"
QT_MOC_LITERAL(13, 234, 17), // "on_twrong_clicked"
QT_MOC_LITERAL(14, 252, 19), // "on_tcorrect_clicked"
QT_MOC_LITERAL(15, 272, 15), // "on_tadd_clicked"
QT_MOC_LITERAL(16, 288, 18), // "on_tdelete_clicked"
QT_MOC_LITERAL(17, 307, 7), // "message"
QT_MOC_LITERAL(18, 315, 1) // "s"

    },
    "MainWindow\0on_open_triggered\0\0"
    "on_addtable_triggered\0on_findtable_triggered\0"
    "on_backbutton_clicked\0on_pushButton_clicked\0"
    "on_clearbutton_clicked\0on_readtable\0"
    "on_readdb_triggered\0"
    "on_treeWidget_itemSelectionChanged\0"
    "png\0on_trefresh_clicked\0on_twrong_clicked\0"
    "on_tcorrect_clicked\0on_tadd_clicked\0"
    "on_tdelete_clicked\0message\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    2,  100,    2, 0x08 /* Private */,
       9,    0,  105,    2, 0x08 /* Private */,
      10,    0,  106,    2, 0x08 /* Private */,
      11,    0,  107,    2, 0x08 /* Private */,
      12,    0,  108,    2, 0x08 /* Private */,
      13,    0,  109,    2, 0x08 /* Private */,
      14,    0,  110,    2, 0x08 /* Private */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    0,  112,    2, 0x08 /* Private */,
      17,    1,  113,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_open_triggered(); break;
        case 1: _t->on_addtable_triggered(); break;
        case 2: _t->on_findtable_triggered(); break;
        case 3: _t->on_backbutton_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_clearbutton_clicked(); break;
        case 6: _t->on_readtable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 7: _t->on_readdb_triggered(); break;
        case 8: _t->on_treeWidget_itemSelectionChanged(); break;
        case 9: _t->png(); break;
        case 10: _t->on_trefresh_clicked(); break;
        case 11: _t->on_twrong_clicked(); break;
        case 12: _t->on_tcorrect_clicked(); break;
        case 13: _t->on_tadd_clicked(); break;
        case 14: _t->on_tdelete_clicked(); break;
        case 15: _t->message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
