#-------------------------------------------------
#
# Project created by QtCreator 2021-10-01T09:42:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = autologin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login_dialog.cpp \
    file_helper.cpp

HEADERS  += mainwindow.h \
    login_dialog.h \
    file_helper.h

FORMS    += mainwindow.ui \
    login_dialog.ui
