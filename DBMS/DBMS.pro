QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dmdao.cpp \
    field.cpp \
    tree.cpp \
    user.cpp \
    main.cpp \
    mainwindow.cpp \
    login.cpp \
    mydbms.cpp \
    table.cpp

HEADERS += \
    dmdao.h \
    field.h \
    tree.h \
    user.h \
    mainwindow.h \
    login.h \
    mydbms.h \
    tcpsever.h \
    table.h \
    database.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

