TARGET = core
TEMPLATE = lib

FIFTEEN_PUZZLE_PWD = $$PWD/..

QT -= core gui
CONFIG += staticlib
include(../common.pri)

INCLUDEPATH += include

HEADERS += \
    include/board.h \
    include/direction.h \
    include/history.h \
    include/coreexception.h \
    include/state.h \
    include/utils.h \
    include/core.h \
    include/solver.h \
    include/dfssolver.h \
    include/bfssolver.h \
    include/idfssolver.h \
    include/bestfirstsolver.h \
    include/astarsolver.h \
    include/smastarsolver.h

SOURCES += \
    src/board.cpp \
    src/history.cpp \
    src/state.cpp \
    src/utils.cpp \
    src/direction.cpp \
    src/solver.cpp \
    src/dfssolver.cpp \
    src/bfssolver.cpp \
    src/coreexception.cpp \
    src/idfssolver.cpp \
    src/bestfirstsolver.cpp \
    src/astarsolver.cpp \
    src/smastarsolver.cpp

OTHER_FILES += \
    core.pri
