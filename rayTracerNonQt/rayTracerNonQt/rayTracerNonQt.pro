TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    color.cpp \
    point3d.cpp \
    vector3d.cpp \
    scene.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    color.h \
    point3d.h \
    vector3d.h \
    scene.h

