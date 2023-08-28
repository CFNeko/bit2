#-------------------------------------------------
#
# Project created by QtCreator 2020-08-25T00:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = combobox
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    combobox.cpp \
    listwidget.cpp \
    tablewidget.cpp

HEADERS  += widget.h \
    combobox.h \
    listwidget.h \
    tablewidget.h

FORMS    += widget.ui \
    listwidgetItem.ui

RESOURCES += \
    resource/combobox.qrc
