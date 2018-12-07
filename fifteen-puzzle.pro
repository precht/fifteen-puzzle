TEMPLATE = subdirs

SUBDIRS += \
    core \
    core-tests \
    cli \
    gui

core-tests.depends = core
cli.depends = core
gui.depends = core

OTHER_FILES += \
    common.pri
