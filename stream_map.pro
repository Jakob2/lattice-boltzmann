#-------------------------------------------------
#
# Project created by QtCreator 2017-05-27T19:59:24
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = stream_map
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    lb.cpp \
    grid.cpp \
    wall.cpp \
    gui.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    global.h \
    lb.h \
    grid.h \
    wall.h \
    gui.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU

QMAKE_CXXFLAGS += -std=c++11

