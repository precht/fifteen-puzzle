#QML_IMPORT_PATH = /opt/qt \

QT += quick quickcontrols2 widgets

include(../common.pri)
include(../core/core.pri)
INCLUDEPATH += include

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    include/boardmodel.h \
    include/config.h \
    include/answear.h \
    include/solverworker.h

SOURCES += \
    src/main.cpp \
    src/boardmodel.cpp \
    src/solverworker.cpp

RESOURCES += qml.qrc
