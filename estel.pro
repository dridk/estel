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
    shapewidget.cpp

HEADERS  += gene.h \
    core/genom.h \
    core/life.h \
    core/lifeengine.h \
    qxtjson/qxtjson.h \
    projectfile.h \
    metapolygonitem.h \
    shapewidget.h

INCLUDEPATH+= core qxtjson

FORMS += \
    shapewidget.ui
