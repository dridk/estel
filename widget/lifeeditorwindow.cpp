/***************************************************************************
**                                                                        **
**  FcsViewer, a simple cytometry data viewer made with Qt4 and           **
**  customplot made by Emanuel Eichhammer                                 **
**  Copyright (C) 2013 Sacha Schutz                                       **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author : Sacha Schutz                                        **
**           Website: http://www.labsquare.org                            **
**           Email  : sacha@labsquare.org                                 **
**           Date   : 12.03.12                                            **
****************************************************************************/

#include "lifeeditorwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QFileDialog>
LifeEditorWindow::LifeEditorWindow(QWidget *parent) :
    QDialog(parent)
{
    mToolBar = new QToolBar;
    mEditor = new JSEdit;
    mDebugEdit = new QTextEdit;
    mFormWidget = new LifeFormWidget;
    mEngine = new LifeEngine;
    mScriptEngine = new LifeScriptEngine;
    mDialogBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

    mFormWidget->setMaximumWidth(200);

    QSplitter * centerSplitter = new QSplitter(Qt::Vertical);
    centerSplitter->addWidget(mEditor);
    centerSplitter->addWidget(mDebugEdit);
    centerSplitter->setStretchFactor(1,10);
    centerSplitter->setStretchFactor(0,100);


    QSplitter * mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(mFormWidget);
    mainSplitter->addWidget(centerSplitter);

//    QAction  * saveAction = new QAction(QIcon(":save"),"Save",this);
    QAction  * exportAction = new QAction(QIcon(":upload"),"Export",this);
    QAction  * importAction = new QAction(QIcon(":download"),"Import",this);
    QAction  * stepAction = new QAction(QIcon(":run"),"Test",this);
    QAction  * clearAction = new QAction(QIcon(":clear"),"Clear",this);
    QAction  * helpAction = new QAction(QIcon(":help"), "Help",this);

//    saveAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_S));
    exportAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_E));
    importAction->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_I));






//    connect(saveAction,SIGNAL(triggered()),this,SLOT(accept()));
    connect(exportAction,SIGNAL(triggered()),this,SLOT(exportLife()));
    connect(importAction,SIGNAL(triggered()),this,SLOT(importLife()));
    connect(stepAction,SIGNAL(triggered()),this,SLOT(run()));
    connect(clearAction,SIGNAL(triggered()),this,SLOT(clear()));
    connect(helpAction,SIGNAL(triggered()),this,SLOT(help()));


//    mToolBar->addAction(saveAction);
    mToolBar->addAction(exportAction);
    mToolBar->addAction(importAction);
    mToolBar->addSeparator();
    mToolBar->addAction(stepAction);
    mToolBar->addAction(clearAction);
    mToolBar->addAction(helpAction);
    mToolBar->setIconSize(QSize(16,16));
    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);



    QVBoxLayout * mainLayout = new QVBoxLayout;

    mainLayout->addWidget(mToolBar);
    mainLayout->addWidget(mainSplitter);
    mainLayout->addWidget(mDialogBox);
    setLayout(mainLayout);

    connect(mDialogBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(mDialogBox,SIGNAL(rejected()),this,SLOT(reject()));

    clear();


}

LifeEditorWindow::~LifeEditorWindow()
{
    delete mEngine;
    delete mToolBar;
    delete mEditor;
    delete mDebugEdit;
    delete mFormWidget;
    delete mScriptEngine;
}

void LifeEditorWindow::setLife(const Life &life)
{
    mLife = life;
    mFormWidget->setLife(life);
    mEditor->setPlainText(life.script());
}

const Life &LifeEditorWindow::life()
{
    mLife = mFormWidget->life();
    mLife.setScript(mEditor->toPlainText());
    return mLife;
}

void LifeEditorWindow::importLife()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,"Save life","", "Lifes (*.life)");

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    Life::parse(file.readAll(), &mLife);
    file.close();
    setLife(mLife);
}

void LifeEditorWindow::exportLife()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,"Save life","", "Lifes (*.life)");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;

    mLife = life();
    file.write(Life::serialize(&mLife).toUtf8());
    file.close();

}

void LifeEditorWindow::clear()
{
    mEngine->clear();
    mDebugEdit->clear();
    mEngine->addLife(&mLife);
}

void LifeEditorWindow::run()
{
    Life tempLife = life();
    mEngine->clear();
    mScriptEngine->setLifeEngine(mEngine);
    mEngine->addLife(&tempLife);
    bool result = mScriptEngine->evaluateLife(&tempLife);

    if (!mScriptEngine->lastError().isEmpty())
        mDebugEdit->append(QString("<font color='red'>%1</font>").arg(mScriptEngine->lastError()));

    if (!mScriptEngine->lastDebug().isEmpty())
        mDebugEdit->append(QString("<i><font color='darkgray'>%1</font></i>").arg(mScriptEngine->lastDebug()));

    mDebugEdit->append(QString("<font color='green'>Life returned %1</font>").arg(result?"LIVE":"DEAD"));
    mEngine->step();


}

void LifeEditorWindow::help()
{
}

