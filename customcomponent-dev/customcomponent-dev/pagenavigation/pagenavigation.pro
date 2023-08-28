#-------------------------------------------------
#
# Project created by QtCreator 2022-07-11T21:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pagenavigation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    button_number.cpp \
    page_navigation_widget.cpp

HEADERS  += mainwindow.h \
    button_number.h \
    page_navigation_defines.h \
    page_navigation_widget.h

FORMS    += mainwindow.ui \
    page_navigation_widget.ui

RESOURCES += \
    resource/pagenavigation.qrc
