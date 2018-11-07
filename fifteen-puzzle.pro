TEMPLATE = subdirs

SUBDIRS += \
    core \
    core-tests \
    cli \

cli.depends = core
core-tests.depends = core
