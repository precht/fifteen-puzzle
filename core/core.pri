LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a
