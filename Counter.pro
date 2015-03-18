QT += core gui opengl quick svg xml qml declarative multimedia widgets

TARGET = Counter
TEMPLATE = app

SOURCES += main.cpp\
       countermainwindow.cpp \
    imageviewer.cpp \
    counter.cpp \
    counterviewer.cpp \
    mergesort.cpp \
    motionanalyzer.cpp

HEADERS  += countermainwindow.h \
    imageviewer.h \
    counter.h \
    counterviewer.h \
    mergesort.h \
    motionanalyzer.h

FORMS  +=  countermainwindow.ui

INCLUDEPATH += /usr/local/include/
LIBS += /usr/local/lib/*.so.2.4.8

