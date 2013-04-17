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
#    projectfile.cpp \
#    metapolygonitem.cpp \
#    shapewidget.cpp \
    widget/lifeengineview.cpp \
    widget/gridview.cpp \
    widget/lifedialog.cpp \
#    script/scriptlife.cpp \
#    widget/simulationdialog.cpp \
#    widget/lifeeditor.cpp \
    widget/genedialog.cpp \
   jsedit/jsedit.cpp \
#    widget/simmainwindow.cpp \
#    widget/animmainwindow.cpp \
    widget/actionlistview.cpp \
    widget/genomview.cpp \
    widget/colorgradientwidget.cpp \
    widget/colorbutton.cpp \
    widget/lifelistview.cpp \
    mainwindow.cpp \
    widget/genecombobox.cpp \
    widget/lifeengineviewfilterwidget.cpp \
    widget/lifeengineviewfilterdelegate.cpp \
    widget/lifefilterwidget.cpp \
    widget/qcustomplot.cpp \
    widget/lifeplotwidget.cpp \
    widget/geneplotwidget.cpp \
    widget/lifescripteditor.cpp \
    widget/previewwidget.cpp \
    core/lifescriptengine.cpp \
    widget/lifeformwidget.cpp
#    qxtjson/jsonmodel.cpp \
#    widget/lifefileview.cpp \
#    widget/addlifecommand.cpp \
#    widget/aboutdialog.cpp

HEADERS  += gene.h \
    core/genom.h \
    core/life.h \
    core/lifeengine.h \
    qxtjson/qxtjson.h \
#    projectfile.h \
#    metapolygonitem.h \
#    shapewidget.h \
    widget/lifeengineview.h \
    widget/gridview.h \
    widget/lifedialog.h \
#    script/scriptlife.h \
#    widget/simulationdialog.h \
#    widget/lifeeditor.h \
    widget/genedialog.h \
    jsedit/jsedit.h \
#    widget/simmainwindow.h \
#    widget/animmainwindow.h \
    widget/actionlistview.h \
 #  widget/lifefileview.h
   widget/genomview.h \
    widget/colorgradientwidget.h \
    widget/colorbutton.h \
    widget/lifelistview.h \
    mainwindow.h \
    widget/genecombobox.h \
    widget/lifeengineviewfilterwidget.h \
    widget/lifeengineviewfilterdelegate.h \
    widget/lifefilterwidget.h \
    widget/qcustomplot.h \
    widget/lifeplotwidget.h \
    widget/geneplotwidget.h \
    widget/lifescripteditor.h \
    widget/previewwidget.h \
    core/lifescriptengine.h \
    widget/lifeformwidget.h
#    qxtjson/jsonmodel.h \
#    widget/addlifecommand.h \
#    widget/aboutdialog.h

INCLUDEPATH+= core qxtjson widget script jsedit

FORMS += \
#    shapewidget.ui \
#    widget/lifedialog.ui \
#    mainwindow.ui \
#    widget/simulationdialog.ui \
#    widget/lifeeditor.ui \
#    widget/genedialog.ui \
#    widget/simmainwindow.ui \
#    widget/animmainwindow.ui \
#    widget/aboutdialog.ui
    mainwindow.ui

RESOURCES += \
    jsedit/testeditor.qrc \
    gfx/gfx.qrc

