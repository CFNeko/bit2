#-------------------------------------------------
#
# Project created by QtCreator 2021-02-27T11:40:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = messagecenter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    messagecenter.cpp

HEADERS  += mainwindow.h \
    messagecenter.h

FORMS    += mainwindow.ui \
    msgitem.ui \
    messagecenter.ui

RESOURCES += \
    messagecenter.qrc
