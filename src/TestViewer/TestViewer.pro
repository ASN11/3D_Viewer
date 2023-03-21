QT += testlib core opengl openglwidgets
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

include(../model/gifimage/qtgifimage.pri)

SOURCES +=  tst_parsertest.cpp \
    ../model/parser.cpp \
    ../model/scene.cpp \
    ../model/simpleobject3d.cpp

HEADERS += \
    ../model/parser.h \
    ../model/scene.h \
    ../model/simpleobject3d.h

RESOURCES += \
    ../model/shaders.qrc

DISTFILES += \
    ../model/vshader.vsh
