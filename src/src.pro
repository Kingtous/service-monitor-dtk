QT += core gui dtkwidget

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = service_monitor
TEMPLATE = app

SOURCES += \
        main.cpp \
    mainframe.cpp \
    servicemonitorproxy.cpp \
    servicerequesttask.cpp \
    servicemonitor.cpp \
    baseservicemonitor.cpp \
    baseservicemonitortask.cpp \
    httpservicemonitortask.cpp \
    servicegroup.cpp \
    serviceitem.cpp \
    servicegrouprepo.cpp \
    servicemonitorsetting.cpp \
    addservicegroup.cpp \
    dashboard.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainframe.h \
    servicemonitorproxy.h \
    servicerequesttask.h \
    servicemonitor.h \
    baseservicemonitor.h \
    baseservicemonitortask.h \
    httpservicemonitortask.h \
    servicegroup.h \
    serviceitem.h \
    servicegrouprepo.h \
    servicemonitorsetting.h \
    addservicegroup.h \
    dashboard.h

FORMS += \
    leftsidebar.ui \
    dashboard.ui \
    service_manage.ui \
    addservicegroup.ui
