#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T14:48:21
#
#-------------------------------------------------

QT       += script core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = estel
TEMPLATE = app
CONFIG+=thread

SOURCES += main.cpp\
    core/gene.cpp \
    core/genom.cpp \
    core/life.cpp \
    core/lifeengine.cpp \
    qxtjson/qxtjson.cpp \
    widget/lifeengineview.cpp \
    widget/lifedialog.cpp \
    widget/genedialog.cpp \
   jsedit/jsedit.cpp \
    widget/actionlistview.cpp \
    widget/genomview.cpp \
    widget/colorgradientwidget.cpp \
    widget/colorbutton.cpp \
    widget/lifelistview.cpp \
    mainwindow.cpp \
    widget/genecombobox.cpp \
    widget/lifefilterwidget.cpp \
    widget/qcustomplot.cpp \
    widget/lifeplotwidget.cpp \
    widget/geneplotwidget.cpp \
    widget/lifescripteditor.cpp \
    widget/previewwidget.cpp \
    core/lifescriptengine.cpp \
    widget/lifeformwidget.cpp \
    widget/lifeeditorwindow.cpp \
    widget/progressstatusbar.cpp \
    widget/gridwidget.cpp \
    widget/gridview.cpp \
    widget/bottomtoolbar.cpp \
    core/lifeenginethread.cpp


HEADERS  += gene.h \
    core/genom.h \
    core/life.h \
    core/lifeengine.h \
    qxtjson/qxtjson.h \
    widget/lifeengineview.h \
    widget/lifedialog.h \
    widget/genedialog.h \
    jsedit/jsedit.h \
    widget/actionlistview.h \
   widget/genomview.h \
    widget/colorgradientwidget.h \
    widget/colorbutton.h \
    widget/lifelistview.h \
    mainwindow.h \
    widget/genecombobox.h \
    widget/lifefilterwidget.h \
    widget/qcustomplot.h \
    widget/lifeplotwidget.h \
    widget/geneplotwidget.h \
    widget/lifescripteditor.h \
    widget/previewwidget.h \
    core/lifescriptengine.h \
    widget/lifeformwidget.h \
    widget/lifeeditorwindow.h \
    core/gene.h \
    widget/progressstatusbar.h \
    widget/gridwidget.h \
    widget/gridview.h \
    widget/bottomtoolbar.h \
    core/lifeenginethread.h


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

