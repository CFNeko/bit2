#-------------------------------------------------
#
# Project created by QtCreator 2020-08-18T22:29:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maskwidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mask_widget.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    mask_widget.h \
    dialog.h

FORMS    += mainwindow.ui \
    mask_widget.ui \
    dialog.ui
