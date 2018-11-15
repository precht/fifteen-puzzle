TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

include(../core/core.pri)
include(../common.pri)

DISTFILES += \
    input
