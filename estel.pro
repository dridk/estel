#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T14:48:21
#
#-------------------------------------------------

QT       += core gui

TARGET = estel
TEMPLATE = app


SOURCES += main.cpp\
    core/gene.cpp \
    core/genom.cpp \
    core/life.cpp \
    core/lifeengine.cpp \
    qxtjson/qxtjson.cpp \
    projectfile.cpp \
    metapolygonitem.cpp \
    shapewidget.cpp \
    core/project.cpp \
    widget/lifeengineview.cpp \
    widget/gridwidget.cpp \
    widget/gridview.cpp

HEADERS  += gene.h \
    core/genom.h \
    core/life.h \
    core/lifeengine.h \
    qxtjson/qxtjson.h \
    projectfile.h \
    metapolygonitem.h \
    shapewidget.h \
    core/project.h \
    widget/lifeengineview.h \
    widget/gridwidget.h \
    widget/gridview.h

INCLUDEPATH+= core qxtjson widget

FORMS += \
    shapewidget.ui
