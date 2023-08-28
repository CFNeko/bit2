#-------------------------------------------------
#
# Project created by QtCreator 2022-12-14T22:06:31
#
#-------------------------------------------------

QT += charts
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chart
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    barchart.cpp \
    linechart.cpp \
    piechart.cpp \
    tabledata.cpp

HEADERS  += mainwindow.h \
    barchart.h \
    linechart.h \
    piechart.h \
    tabledata.h

FORMS    += mainwindow.ui \
    barchart.ui \
    linechart.ui \
    piechart.ui \
    tabledata.ui
