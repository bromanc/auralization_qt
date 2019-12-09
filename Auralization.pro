#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T15:05:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Auralization
TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS *= -fopenmp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    plane.cpp \
    planelayer.cpp \
    point.cpp \
    ray.cpp \
    receiver.cpp \
    receiverlayer.cpp \
    reflector.cpp \
    room.cpp \
    source.cpp \
    sourcelayer.cpp \
    triangle.cpp \
    sphere.cpp \
    vector.cpp \
    octree.cpp \
    ofxConvexHull/libs/Tests/QuickHullTests.cpp \
    ofxConvexHull/libs/QuickHull.cpp \
    ofxConvexHull/src/ofxConvexHull.cpp \
    glwidget.cpp

HEADERS += \
    definitions.h \
    mainwindow.h \
    plane.h \
    planelayer.h \
    point.h \
    ray.h \
    receiver.h \
    receiverlayer.h \
    reflector.h \
    room.h \
    source.h \
    sourcelayer.h \
    triangle.h \
    sphere.h \
    intersectioninfo.h \
    vector.h \
    octree.h \
    ofxConvexHull/libs/Structs/Mesh.hpp \
    ofxConvexHull/libs/Structs/Plane.hpp \
    ofxConvexHull/libs/Structs/Pool.hpp \
    ofxConvexHull/libs/Structs/Ray.hpp \
    ofxConvexHull/libs/Structs/Vector3.hpp \
    ofxConvexHull/libs/Structs/VertexDataSource.hpp \
    ofxConvexHull/libs/Tests/QuickHullTests.hpp \
    ofxConvexHull/libs/ConvexHull.hpp \
    ofxConvexHull/libs/HalfEdgeMesh.hpp \
    ofxConvexHull/libs/MathUtils.hpp \
    ofxConvexHull/libs/QuickHull.hpp \
    ofxConvexHull/libs/Types.hpp \
    ofxConvexHull/src/ofxConvexHull.h \
    glwidget.h \
    raytracer.h \
    impulseresponse.h \
    bandenergy.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc
