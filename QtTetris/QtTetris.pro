#-------------------------------------------------
#
# Project created by QtCreator 2015-06-27T02:57:32
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
DESTDIR   = $$PWD

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTetris
TEMPLATE = app

CONFIG += c++11
CONFIG+=sdk_no_version_check

SOURCES += main.cpp\
        mainwindow.cpp \
    area.cpp \
    number.cpp \
    tile.cpp

HEADERS  += mainwindow.h \
    area.h \
    number.h \
    tile.h

RESOURCES += \
    resource.qrc

FORMS += \
    mainwindow.ui
