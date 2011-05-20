QT += core gui
DESTDIR = ./

TARGET = cellular
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    Cell.cpp \
    NewSimDialog.cpp \
    GridWidget.cpp

HEADERS  += MainWindow.h \
    Cell.h \
    NewSimDialog.h \
    GridWidget.h

LIBS += -llua5.1
