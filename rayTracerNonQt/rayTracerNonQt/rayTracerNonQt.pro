TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    color.cpp \
    point3d.cpp \
    vector3d.cpp \
    scene.cpp \
    light.cpp \
    material.cpp \
    camera.cpp \
    drawableobject.cpp \
    intersection.cpp \
    tringle.cpp \
    sphere.cpp \
    ray.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    color.h \
    point3d.h \
    vector3d.h \
    scene.h \
    light.h \
    material.h \
    camera.h \
    drawableobject.h \
    intersection.h \
    ray.h \
    tringle.h \
    sphere.h

