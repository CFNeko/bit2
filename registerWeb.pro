QT       += core gui sql network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    booking.cpp \
    doctorpage.cpp \
    healthevaluation.cpp \
    homepage.cpp \
    main.cpp \
    mainwidget.cpp \
    navigationdesign.cpp \
    prescriptioninquiry.cpp \
    prescriptionpatient.cpp \
    prescriptiontable.cpp \
    qmybutton.cpp \
    qmylabel.cpp \
    qmywidget.cpp \
    recorditeminquiry.cpp \
    recorditempatient.cpp \
    recorditemtable.cpp \
    registerweb.cpp \
    registraitondoctorpage.cpp \
    signup.cpp \
    userfriendlyitems.cpp \
    dbwidget.cpp \
    entereventfilter.cpp \
    message.cpp \
    patientchatwidget.cpp

HEADERS += \
    booking.h \
    doctorpage.h \
    healthevaluation.h \
    homepage.h \
    mainwidget.h \
    navigationdesign.h \
    prescriptioninquiry.h \
    prescriptionpatient.h \
    prescriptiontable.h \
    qmybutton.h \
    qmylabel.h \
    qmywidget.h \
    recorditeminquiry.h \
    recorditempatient.h \
    recorditemtable.h \
    registerweb.h \
    registraitondoctorpage.h \
    signup.h \
    userfriendlyitems.h \
    dbwidget.h \
    entereventfilter.h \
    message.h \
    patientchatwidget.h

FORMS += \
    booking.ui \
    doctorpage.ui \
    healthevaluation.ui \
    homepage.ui \
    listtemplate.ui \
    mainwidget.ui \
    msgitem.ui \
    navigationdesign.ui \
    prescriptioninquiry.ui \
    prescriptionpatient.ui \
    prescriptiontable.ui \
    recorditeminquiry.ui \
    recorditempatient.ui \
    recorditemtable.ui \
    registerweb.ui \
    registraitondoctorpage.ui \
    signup.ui \
    userfriendlyitems.ui \
    dbwidget.ui \
    message.ui \
    patientchatwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    customcomponent-dev/customcomponent-dev/listwidget/listwidget.qrc \
    myresource/chatResourse.qrc \
    resources.qrc

DISTFILES += \
    resource111/logo.jpg

SUBDIRS += \
    uidemo08/uidemo08.pro
