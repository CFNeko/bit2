#-------------------------------------------------
#
# Project created by QtCreator 2020-08-26T23:43:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = passwdcheck
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    passwd_check_widget.cpp

HEADERS  += mainwindow.h \
    passwd_check_widget.h

FORMS    += mainwindow.ui \
    passwd_check_widget.ui
