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
    widget/lifeengineview.cpp \
    widget/gridwidget.cpp \
    widget/gridview.cpp \
    widget/lifedialog.cpp \
#    script/scriptlife.cpp \
    mainwindow.cpp \
    widget/simulationdialog.cpp \
    widget/lifeeditor.cpp \
    widget/genedialog.cpp \
    jsedit/jsedit.cpp \
    widget/simmainwindow.cpp \
    widget/animmainwindow.cpp \
    widget/actionlistview.cpp \
    widget/lifefileview.cpp \
    widget/lifesview.cpp

HEADERS  += gene.h \
    core/genom.h \
    core/life.h \
    core/lifeengine.h \
    qxtjson/qxtjson.h \
    projectfile.h \
    metapolygonitem.h \
    shapewidget.h \
    widget/lifeengineview.h \
    widget/gridwidget.h \
    widget/gridview.h \
    widget/lifedialog.h \
#    script/scriptlife.h \
    mainwindow.h \
    widget/simulationdialog.h \
    widget/lifeeditor.h \
    widget/genedialog.h \
    jsedit/jsedit.h \
    widget/simmainwindow.h \
    widget/animmainwindow.h \
    widget/actionlistview.h \
    widget/lifefileview.h \
    widget/lifesview.h

INCLUDEPATH+= core qxtjson widget script jsedit

FORMS += \
    shapewidget.ui \
    widget/lifedialog.ui \
    mainwindow.ui \
    widget/simulationdialog.ui \
    widget/lifeeditor.ui \
    widget/genedialog.ui \
    widget/simmainwindow.ui \
    widget/animmainwindow.ui

RESOURCES += \
    jsedit/testeditor.qrc \
    gfx/gfx.qrc

