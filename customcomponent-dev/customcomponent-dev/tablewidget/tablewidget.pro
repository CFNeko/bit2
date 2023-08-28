#-------------------------------------------------
#
# Project created by QtCreator 2021-10-28T22:59:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tablewidget
TEMPLATE = app

INCLUDEPATH += ..\pagenavigation\

SOURCES += main.cpp\
        mainwindow.cpp \
    check_box.cpp \
    table_widget.cpp \
    table_head_cell_widget.cpp \
    table_operate_widget.cpp \
    operate_button.cpp  \
    ../pagenavigation/page_navigation_widget.cpp \
    ../pagenavigation/button_number.cpp

HEADERS  += mainwindow.h \
    check_box.h \
    table_widget.h \
    table_defines.h \
    table_head_cell_widget.h \
    table_operate_widget.h \
    operate_button.h    \
    ../pagenavigation/page_navigation_defines.h \
    ../pagenavigation/page_navigation_widget.h \
    ../pagenavigation/button_number.h

FORMS    += mainwindow.ui \
    table_widget.ui \
    table_head_cell_widget.ui \
    table_operate_widget.ui \
    ../pagenavigation/page_navigation_widget.ui

RESOURCES += \
    resource/table.qrc
