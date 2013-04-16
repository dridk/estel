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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mEngine = new LifeEngine(500,500);
    mEngineView = new LifeEngineView;
    mLifeListView = new LifeListView;
    mLifePlotWidget = new LifePlotWidget;
    mGenePlotWidget = new GenePlotWidget;
    mLifeFilterWidget = new LifeFilterWidget;

    mEngineView->setEngine(mEngine);
    mLifeListView->setEngine(mEngine);
    mLifePlotWidget->setEngine(mEngine);
    mGenePlotWidget->setEngine(mEngine);
    mLifeFilterWidget->setEngineView(mEngineView);


    setCentralWidget(mEngineView);

    QDockWidget * lifeListDock = new QDockWidget;
    lifeListDock->setWidget(mLifeListView);
    lifeListDock->setWindowTitle(mLifeListView->windowTitle());
    lifeListDock->setWindowIcon(mLifeListView->windowIcon());

    QDockWidget * lifeFilterDock = new QDockWidget;
    lifeFilterDock->setWidget(mLifeFilterWidget);
    lifeFilterDock->setWindowTitle(mLifeFilterWidget->windowTitle());
    lifeFilterDock->setWindowIcon(mLifeFilterWidget->windowIcon());

    QDockWidget * lifePlotDock = new QDockWidget;
    lifePlotDock->setWidget(mLifePlotWidget);
    lifePlotDock->setWindowTitle(mLifePlotWidget->windowTitle());
    lifePlotDock->setWindowIcon(mLifePlotWidget->windowIcon());

    QDockWidget * genePlotDock = new QDockWidget;
    genePlotDock->setWidget(mGenePlotWidget);
    genePlotDock->setWindowTitle(mGenePlotWidget->windowTitle());
    genePlotDock->setWindowIcon(mGenePlotWidget->windowIcon());


    addDockWidget(Qt::LeftDockWidgetArea, lifeListDock);
    addDockWidget(Qt::LeftDockWidgetArea, lifeFilterDock);
    addDockWidget(Qt::LeftDockWidgetArea, lifePlotDock);
    addDockWidget(Qt::RightDockWidgetArea, genePlotDock);




    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(ui->actionStep,SIGNAL(triggered()),mEngine,SLOT(step()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open estel file",
                                                    QString(),"Estel (*.estel)");

    mEngine->load(fileName);
    mLifeListView->refresh();
    setWindowTitle(fileName);


}

void MainWindow::save()
{
    if (windowTitle().isEmpty())
        return;
    mEngine->save(windowTitle());
    setWindowTitle(windowTitle());
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"save estel file",
                                                    QString(),"Estel (*.estel)");
    mEngine->save(fileName);
    setWindowTitle(fileName);

}



