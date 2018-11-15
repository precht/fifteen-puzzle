GOOGLETEST_DIR = /opt/googletest

include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console thread
CONFIG -= qt app_bundle

include(../common.pri)

HEADERS += \
    tst_Board.h \
    tst_HistoryAndState.h \
    tst_Utils.h \
    tst_Solvers.h

SOURCES += \
        main.cpp

include(../core/core.pri)
