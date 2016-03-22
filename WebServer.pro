QT += core network sql
QT -= gui

TARGET = WebServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    webserver.cpp \
    httprequest.cpp \
    webserversettings.cpp \
    httpresponse.cpp \
    httpsocket.cpp \
    controller.cpp \
    application.cpp \
    security.cpp \
    consolerunnable.cpp \
    controllerrunable.cpp

HEADERS += \
    webserver.h \
    httprequest.h \
    webserversettings.h \
    httpresponse.h \
    httpsocket.h \
    controller.h \
    application.h \
    security.h \
    consolerunnable.h \
    controllerrunable.h





