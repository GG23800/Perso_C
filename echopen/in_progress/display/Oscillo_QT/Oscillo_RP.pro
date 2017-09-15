#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T14:56:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Oscillo_RP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tcpparameterwindow.cpp \
    src_RP/TCP_API.cpp \
    qcustomplot.cpp \
    settings.cpp \
    graph.cpp \
    modeb.cpp

HEADERS += \
        mainwindow.h \
    tcpparameterwindow.h \
    src_RP/TCP_API.h \
    qcustomplot.h \
    settings.h \
    graph.h \
    modeb.h

FORMS += \
        mainwindow.ui \
    tcpparameterwindow.ui \
    settings.ui \
    modeb.ui

DISTFILES +=
