#-------------------------------------------------
#
# Project created by QtCreator 2021-02-21T20:24:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    matrixwidget.cpp

HEADERS  += mainwindow.h \
    matrixwidget.h

FORMS    += mainwindow.ui \
    matrixwidget.ui
