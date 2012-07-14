TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x
CXXFLAGS += -std=c++0x


DEFINES += _GXX_EXPERIMENTAL_CXX0X_
DEFINES += __GXX_EXPERIMENTAL_CXX0X__


SOURCES += main.cpp \
    Logger.cpp \
    BinarySerializer.cpp \
    CoreSystem.cpp \
    IIdentifyableTest.cpp

HEADERS += \
    IStreamable.h \
    Logger.h \
    BinarySerializer.h \
    IIdentifyableTest.h \
    CoreSystem.h \
    IIdentifyable.h \
    ISerializer.h

