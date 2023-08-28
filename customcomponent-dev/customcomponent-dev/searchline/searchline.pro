#-------------------------------------------------
#
# Project created by QtCreator 2022-07-07T20:55:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = searchline
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    search_line.cpp

HEADERS  += mainwindow.h \
    search_line.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource/searchline.qrc
