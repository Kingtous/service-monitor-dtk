QT += core gui dtkwidget network charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = service_monitor
TEMPLATE = app

CONFIG += c++17

SOURCES += \
        main.cpp \
    mainframe.cpp \
    addservicegroup.cpp \
    dashboard.cpp \
    servicemanagepage.cpp \
    addservicedialog.cpp \
    latency_chart_list.cpp \
    services_detail_page.cpp

RESOURCES +=         resources.qrc

HEADERS += \
    mainframe.h \
    addservicegroup.h \
    dashboard.h \
    servicemanagepage.h \
    addservicedialog.h \
    latency_chart_list.h \
    services_detail_page.h \
    ui_addservicedialog.h \
    ui_addservicegroup.h \
    ui_dashboard.h \
    ui_leftsidebar.h \
    ui_service_manage.h \

#FORMS += \
#    leftsidebar.ui \
#    dashboard.ui \
#    service_manage.ui \
#    addservicegroup.ui \
#    addservicedialog.ui

include($$PWD/networker/networker.pri)

CONFIG += console


target.source = $$TARGET
target.path = /usr/bin

INSTALLS = target
