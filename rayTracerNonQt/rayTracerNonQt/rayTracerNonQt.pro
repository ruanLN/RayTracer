TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static

SOURCES += main.cpp \
    color.cpp \
    point3d.cpp \
    vector3d.cpp \
    light.cpp \
    material.cpp \
    camera.cpp \
    drawableobject.cpp \
    intersection.cpp \
    triangle.cpp \
    sphere.cpp \
    ray.cpp \
    yaml/aliascontent.cpp \
    yaml/content.cpp \
    yaml/conversion.cpp \
    yaml/emitter.cpp \
    yaml/emitterstate.cpp \
    yaml/emitterutils.cpp \
    yaml/exp.cpp \
    yaml/iterator.cpp \
    yaml/map.cpp \
    yaml/node.cpp \
    yaml/null.cpp \
    yaml/ostream.cpp \
    yaml/parser.cpp \
    yaml/parserstate.cpp \
    yaml/regex.cpp \
    yaml/scalar.cpp \
    yaml/scanner.cpp \
    yaml/scanscalar.cpp \
    yaml/scantoken.cpp \
    yaml/sequence.cpp \
    yaml/simplekey.cpp \
    yaml/stream.cpp \
    scene.cpp \
    png/lodepng.cpp \
    image.cpp \
    objloader.cpp \
    model.cpp \
    plane.cpp \
    box.cpp

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
    triangle.h \
    sphere.h \
    yaml/aliascontent.h \
    yaml/content.h \
    yaml/conversion.h \
    yaml/crt.h \
    yaml/emitter.h \
    yaml/emittermanip.h \
    yaml/emitterstate.h \
    yaml/emitterutils.h \
    yaml/exceptions.h \
    yaml/exp.h \
    yaml/indentation.h \
    yaml/iterator.h \
    yaml/iterpriv.h \
    yaml/ltnode.h \
    yaml/map.h \
    yaml/mark.h \
    yaml/node.h \
    yaml/nodeimpl.h \
    yaml/nodereadimpl.h \
    yaml/nodeutil.h \
    yaml/noncopyable.h \
    yaml/null.h \
    yaml/ostream.h \
    yaml/parser.h \
    yaml/parserstate.h \
    yaml/regex.h \
    yaml/regeximpl.h \
    yaml/scalar.h \
    yaml/scanner.h \
    yaml/scanscalar.h \
    yaml/sequence.h \
    yaml/setting.h \
    yaml/stlemitter.h \
    yaml/stream.h \
    yaml/streamcharsource.h \
    yaml/stringsource.h \
    yaml/token.h \
    yaml/yaml.h \
    png/lodepng.h \
    image.h \
    objloader.h \
    model.h \
    plane.h \
    box.h

DISTFILES +=

