TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    fsm.c \
    display.c \
    keyboard.c \
    collision.c \
    position.c \
    score.c \
    mode.c \
    highscore.c

HEADERS += \
    fsm.h \
    display.h \
    keyboard.h \
    collision.h \
    position.h \
    macros.h \
    score.h \
    mode.h \
    highscore.h
