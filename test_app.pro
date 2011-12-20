TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS += -std=c++0x


DEFINES += _GXX_EXPERIMENTAL_CXX0X_
DEFINES += __GXX_EXPERIMENTAL_CXX0X__


SOURCES += main.cpp \
    KeyValueMap.cpp

HEADERS += \
    IStreamable.h \
    KeyValueMap.h \
    IStreamCoder.h

