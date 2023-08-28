#-------------------------------------------------
#
# Project created by QtCreator 2021-11-21T16:06:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = datetimerange
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    date_time_range_widget.cpp \
    date_time.cpp \
    date_time_edit.cpp

HEADERS  += mainwindow.h \
    date_time_range_widget.h \
    date_time.h \
    date_time_edit.h

FORMS    += mainwindow.ui \
    date_time_range_widget.ui \
    date_time.ui
