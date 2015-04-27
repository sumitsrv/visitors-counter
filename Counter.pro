QT += core gui opengl quick svg xml qml declarative multimedia widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Counter
TEMPLATE = app

SOURCES += main.cpp\
       countermainwindow.cpp \
    imageviewer.cpp \
    counter.cpp \
    counterviewer.cpp \
    mergesort.cpp \
    motionanalyzer.cpp \
    blobinfo.cpp

HEADERS  += countermainwindow.h \
    imageviewer.h \
    counter.h \
    counterviewer.h \
    mergesort.h \
    motionanalyzer.h \
    blobinfo.h

FORMS  +=  countermainwindow.ui

INCLUDEPATH += /usr/local/include/
LIBS += /usr/local/lib/*.so.2.4.8

