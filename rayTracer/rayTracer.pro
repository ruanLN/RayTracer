#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T02:01:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    raytracer.cpp \
    color.cpp \
    vector3d.cpp \
    point3d.cpp

HEADERS  += mainwindow.h \
    raytracer.h \
    color.h \
    vector3d.h \
    point3d.h

FORMS    += mainwindow.ui
