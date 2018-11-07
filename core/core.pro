TARGET = core
TEMPLATE = lib

FIFTEEN_PUZZLE_PWD = $$PWD/..

QT -= core gui
CONFIG += staticlib c++14
QMAKE_CXXFLAGS += -Wshadow

INCLUDEPATH += include

HEADERS += \
    board.h \
    direction.h \
    history.h \
    searchstrategycontainer.h \
    solver.h \
    coreexception.h \
    state.h \
    utils.h \
    dfs.h \
    bfs.h \
    core.h

SOURCES += \
    board.cpp \
    aiexception.cpp \
    history.cpp \
    searchstrategycontainer.cpp \
    solver.cpp \
    state.cpp \
    utils.cpp \
    dfs.cpp \
    bfs.cpp \
    direction.cpp

DISTFILES += \
    core.pri
