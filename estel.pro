#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T14:48:21
#
#-------------------------------------------------

QT       += core gui script

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
    widget/gridview.cpp \
    widget/lifedialog.cpp \
#    script/scriptlife.cpp \
    mainwindow.cpp \
    widget/simulationdialog.cpp \
    widget/lifeeditor.cpp \
    widget/genedialog.cpp \
    jsedit/jsedit.cpp

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
    widget/gridview.h \
    widget/lifedialog.h \
#    script/scriptlife.h \
    mainwindow.h \
    widget/simulationdialog.h \
    widget/lifeeditor.h \
    widget/genedialog.h \
    jsedit/jsedit.h

INCLUDEPATH+= core qxtjson widget script jsedit

FORMS += \
    shapewidget.ui \
    widget/lifedialog.ui \
    mainwindow.ui \
    widget/simulationdialog.ui \
    widget/lifeeditor.ui \
    widget/genedialog.ui

RESOURCES += \
    jsedit/testeditor.qrc

