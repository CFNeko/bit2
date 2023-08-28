#-------------------------------------------------
#
# Project created by QtCreator 2023-04-16T21:17:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commands.cpp \
    image_widget.cpp

HEADERS  += mainwindow.h \
    commands.h \
    draw_tool_defines.h \
    image_widget.h

FORMS    += mainwindow.ui

RESOURCES += \
    painter.qrc
