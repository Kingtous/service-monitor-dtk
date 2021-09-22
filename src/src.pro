QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = service_monitor
TEMPLATE = app

SOURCES += \
        main.cpp \
    mainframe.cpp \
    servicegroup.cpp \
    serviceitem.cpp \
    servicegrouprepo.cpp \
    addservicegroup.cpp \
    dashboard.cpp \
    servicemanagepage.cpp \
    addservicedialog.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainframe.h \
    servicegroup.h \
    serviceitem.h \
    servicegrouprepo.h \
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
