QT += core gui dtkwidget network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = service_monitor
TEMPLATE = app

SOURCES += \
        main.cpp \
    mainframe.cpp \
    addservicegroup.cpp \
    dashboard.cpp \
    servicemanagepage.cpp \
    addservicedialog.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainframe.h \
    addservicegroup.h \
    dashboard.h \
    servicemanagepage.h \
    addservicedialog.h

FORMS += \
    leftsidebar.ui \
    dashboard.ui \
    service_manage.ui \
    addservicegroup.ui \
    addservicedialog.ui

include($$PWD/networker/networker.pri)

CONFIG += console
