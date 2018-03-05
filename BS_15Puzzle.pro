TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    state.cpp \
    beamsearch.cpp \
    astar.cpp

HEADERS += \
    state.h \
    beamsearch.h \
    astar.h
