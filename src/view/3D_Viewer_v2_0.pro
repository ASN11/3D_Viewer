QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../model/gifimage/qtgifimage.pri)

SOURCES += \
    ../controller/controller.cpp \
    ../model/parser.cpp \
    ../model/scene.cpp \
    ../model/simpleobject3d.cpp \
    main.cpp \
    view.cpp

HEADERS += \
    ../controller/controller.h \
    ../model/parser.h \
    ../model/scene.h \
    ../model/simpleobject3d.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../model/shaders.qrc

DISTFILES += \
    ../model/fshader.fsh \
    ../model/vshader.vsh

