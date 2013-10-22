#-------------------------------------------------
#
# Project created by QtCreator 2013-10-15T10:39:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): {
  QT += widgets opengl
  CONFIG += C++11
}


TARGET = Simulator3C
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    widget.cpp \
    renderwidget.cpp \
    VTF/threading/atomics.cpp \
    VTF/math.cpp \
    VTF/pointer/RefObject.cpp \
    VTF/exceptions/exceptions.cpp \
    VBGL/GLRenderer.cpp \
    VBGL/Camera.cpp \
    VBGL/PerspectiveCamera.cpp \
    VBGL/Scene.cpp \
    VBGL/Object3D.cpp \
    VBGL/OrthographicCamera.cpp \
    VBGL/Material.cpp \
    VBGL/core/GLCaps.cpp \
    VBGL/core/shader.cpp \
    VBGL/core/texture2d.cpp \
    VBGL/core/Geometry.cpp \
    VBGL/core/GLStateManager.cpp \
    VBGL/core/arrayBuffer.cpp \
    VBGL/Mesh.cpp \
    model.cpp \
    Paths/parser.cpp \
    Paths/commands.cpp \
    originaxismodel.cpp

HEADERS  += mainwindow.h \
    widget.h \
    renderwidget.h \
    VTF/threading/atomics.h \
    VTF/traits.h \
    VTF/math.h \
    VTF/pointer/RefObject.h \
    VTF/pointer/ownptr.h \
    VTF/pointer/refptr.h \
    VTF/exceptions/exceptions.h \
    VTF/Traits \
    VTF/Math \
    VTF/VTF \
    VTF/Pointers \
    VTF/Exception \
    VBGL/Mesh.h \
    VBGL/Scene.h \
    VBGL/Camera.h \
    VBGL/Material.h \
    VBGL/PerspectiveCamera.h \
    VBGL/Object3D.h \
    VBGL/GLRenderer.h \
    VBGL/core/myGL.h \
    VBGL/core/Geometry.h \
    VBGL/core/GLStateManager.h \
    VBGL/core/shader.h \
    VBGL/core/texture2d.h \
    VBGL/core/arrayBuffer.h \
    VBGL/core/GLCaps.h \
    VBGL/OrthographicCamera.h \
    VBGL/VBGL \
    VBGL/core/GLExts.inl \
    VBGL/core/Core \
    model.h \
    Paths/commands.h \
    Paths/parser.h \
    originaxismodel.h


FORMS    += mainwindow.ui

LIBS += -lGLEW -lGLU
