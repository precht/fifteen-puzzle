GOOGLETEST_DIR = /opt/googletest

include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console thread
CONFIG -= qt app_bundle

include(../common.pri)

HEADERS += \
    tst_heuristic.h \
    tst_board.h \
    tst_solvers.h \
    tst_utils.h \
    tst_history_state.h

SOURCES += \
        main.cpp

include(../core/core.pri)
