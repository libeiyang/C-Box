TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++20
INCLUDEPATH += /home/stef/Downloads/boost_1_77_0_rc1/boost_1_77_0

SOURCES += \
        Box.cpp \
        main.cpp \
        thoughpack.cpp \
        truckload.cpp

HEADERS += \
    Box.h \
    thoughpack.h \
    truckload.h
