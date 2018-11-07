include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++14 thread
CONFIG -= qt app_bundle

HEADERS += \
    tst_Board.h \
    tst_HistoryAndState.h \
    tst_Utils.h \
    tst_SearchStrategy.h

SOURCES += \
        main.cpp

include(../core/core.pri)
