#-------------------------------------------------
#
# Project created by QtCreator 2021-02-24T22:12:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

windows {
     DEFINES *= Q_COMPILER_INITIALIZER_LISTS
}

TARGET = mainWindow
TEMPLATE = app


SOURCES += main.cpp\
        view\frame\mainwindow.cpp \
    view/frame/menu_bar_widget.cpp \
    view/frame/menu_button.cpp \
    view/frame/status_bar_widget.cpp \
    view/frame/title_bar_widget.cpp \
    view/basewidget/base_widget.cpp \
    view/maskwidget/mask_widget.cpp \
    view/frame/globalapplication.cpp \
    view/frame/tab_cell_widget.cpp \
    view/systemset/testwidget.cpp


HEADERS  += view\frame\mainwindow.h \
    view/frame/menu_bar_widget.h \
    view/frame/menu_button.h \
    view/frame/status_bar_widget.h \
    view/frame/title_bar_widget.h \
    view/basewidget/base_widget.h \
    view/maskwidget/mask_widget.h \
    view/frame/globalapplication.h \
    view/frame/tab_cell_widget.h \
    view/frame/menu_defines.h \
    view/systemset/testwidget.h


FORMS    += view\frame\mainwindow.ui \
    view/frame/menu_bar_widget.ui \
    view/frame/status_bar_widget.ui \
    view/frame/title_bar_widget.ui \
    view/maskwidget/mask_widget.ui \
    view/frame/tab_cell_widget.ui \
    view/systemset/testwidget.ui

INCLUDEPATH += $$PWD\view \
    $$PWD\view\frame \
    $$PWD\view\maskwidget \
    $$PWD\view\basewidget \
    $$PWD\view\systemset \

RESOURCES += \
   $$PWD\resource\main.qrc
