TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    epoll_server.cpp

HEADERS += \
    epoll_server.h

