#-------------------------------------------------
#
# Project created by QtCreator 2023-05-26T21:22:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colordialog
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    color_widget.cpp \
    color_coustom_widget.cpp

HEADERS  += mainwindow.h \
    color_widget.h \
    color_coustom_widget.h

FORMS    += mainwindow.ui \
    color_widget.ui

RESOURCES += \
    color_dialog.qrc
