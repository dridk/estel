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

    mEngine           = new LifeEngine(500,500);
    mEngineThread     = new LifeEngineThread;
    mEngineView       = new LifeEngineView;
    mLifeListView     = new LifeListView;
    mLifePlotWidget   = new LifePlotWidget;
    mGenePlotWidget   = new GenePlotWidget;
    mLifeFilterWidget = new LifeFilterWidget;
    mPreviewWidget    = new PreviewWidget;
    mStatusBar        = new ProgressStatusBar;
    mBottomBar        = new BottomToolBar;
    mBrowserWidget    = new EstelBrowserWidget;

    mEngineThread->setEngine(mEngine);
    mEngineView->setEngine(mEngine);
    mLifeListView->setEngine(mEngine);
    mLifePlotWidget->setEngine(mEngine);
    mGenePlotWidget->setEngineView(mEngineView);
    mLifeFilterWidget->setEngineView(mEngineView);
    mPreviewWidget->setEngineView(mEngineView);
    mBottomBar->setEngineView(mEngineView);

    setCentralWidget(mEngineView);
    addToolBar(Qt::BottomToolBarArea, mBottomBar);


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

    QDockWidget * previewDock = new QDockWidget;
    previewDock->setWidget(mPreviewWidget);
    previewDock->setWindowTitle(mPreviewWidget->windowTitle());
    previewDock->setWindowIcon(mPreviewWidget->windowIcon());

    QDockWidget * browserDock = new QDockWidget;
    browserDock->setWidget(mBrowserWidget);
    browserDock->setWindowTitle(mBrowserWidget->windowTitle());
    browserDock->setWindowIcon(mBrowserWidget->windowIcon());


    addDockWidget(Qt::LeftDockWidgetArea, lifeListDock);
    addDockWidget(Qt::LeftDockWidgetArea, lifeFilterDock);
    addDockWidget(Qt::LeftDockWidgetArea, lifePlotDock);
    addDockWidget(Qt::RightDockWidgetArea, genePlotDock);
    addDockWidget(Qt::RightDockWidgetArea, previewDock);
    addDockWidget(Qt::RightDockWidgetArea, browserDock);





    //setStatusBar(mStatusBar);

    connect(ui->actionLifeList,SIGNAL(triggered(bool)),lifeListDock,SLOT(setVisible(bool)));
    connect(ui->actionLifeFilter,SIGNAL(triggered(bool)),lifeListDock,SLOT(setVisible(bool)));
    connect(ui->actionLifePlot,SIGNAL(triggered(bool)),lifePlotDock,SLOT(setVisible(bool)));
    connect(ui->actionGenePlot,SIGNAL(triggered(bool)),genePlotDock,SLOT(setVisible(bool)));
    connect(ui->actionMiniMap,SIGNAL(triggered(bool)),previewDock,SLOT(setVisible(bool)));




    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(ui->actionStep,SIGNAL(triggered()),mEngineThread,SLOT(step()));
    connect(ui->actionClear,SIGNAL(triggered()),mEngine,SLOT(clear()));
    connect(ui->actionExport,SIGNAL(triggered()),this,SLOT(exportImage()));
    connect(mEngineThread,SIGNAL(runningChanged(bool)),this,SLOT(setDisabled(bool)));
    connect(mEngineThread,SIGNAL(finished()),this,SLOT(refresh()));
    connect(mEngine,SIGNAL(progress(int,QString)),mBottomBar,SLOT(setProgress(int,QString)));
    connect(mBrowserWidget,SIGNAL(fileSelected(QString)),this,SLOT(open(QString)));
    connect(ui->actionMakeSim,SIGNAL(triggered()),this,SLOT(makeSimulation()));


    showMaximized();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(const QString &fileName)
{
    //    setEnabled(false);
    mStatusBar->setActive(true);
    QString name = fileName;
    if (name.isEmpty())
        name = QFileDialog::getOpenFileName(this,"open estel file",
                                            QString(),"Estel (*.estel)");


    mEngineThread->load(name);
    mLifeListView->refresh();
    setWindowTitle(name);
    mStatusBar->setActive(false);

}

void MainWindow::save()
{
    if (windowTitle().isEmpty())
    {
        saveAs();
        return;
    }

    mEngineThread->save(windowTitle());
    setWindowTitle(windowTitle());
}

void MainWindow::saveAs(const QString &fileName)
{
    QString name = fileName;
    if (name.isEmpty())
        name = QFileDialog::getSaveFileName(this,"save estel file",
                                            QString(),"Estel (*.estel)");
    mEngineThread->save(name);
    setWindowTitle(name);

}
void MainWindow::makeSimulation()
{
    int iteration = 2;
    QString name = QFileDialog::getExistingDirectory(this,"save simulation");
    QDir dir(name);
    dir.mkdir("estel");
    dir.mkdir("cache");
    QVariantMap data;


    for (int i=0; i<iteration; ++i)
    {

        QString estelFile = dir.path() + QDir::separator() + "estel" + QDir::separator()+ QString("step_%1.estel").arg(i);
        QString cacheFile = dir.path() + QDir::separator() + "cache" + QDir::separator()+ QString("step_%1.png").arg(i);

        QVariantList lifesList;

//        foreach (Life * life, mEngine->lifes())
//        {
//            QVariantMap lifeData;
//            QVariantMap geneData;

//            lifeData[life->name()] = life->name();
//            if (!lifeData.contains("population"))
//                lifeData["population"] = 0;
//            lifeData["population"] = lifeData["population"].toInt() + 1;

//            foreach ( Gene gene, life->genom().genes())
//            {
//                geneData[gene.name()] = gene.name();



//            }

//        }



        mEngine->save(estelFile);
        mEngine->toPixmap().save(cacheFile);
        mEngine->step();



    }

    QVariantMap simInfo;
    simInfo["date"]   = QDateTime::currentDateTime().toString(Qt::ISODate);
    simInfo["author"] = "sacha schutz";
    simInfo["duration"] = 454231;





    data["simulation"] = simInfo;






}

void MainWindow::exportImage()
{
    QString filename = QFileDialog::getSaveFileName();

    //    mEngineView->view()->showGrid(false);
    //    mEngineView->view()->snap()->save(filename);
    //    mEngineView->view()->showGrid(true);


}

void MainWindow::refresh()
{
    mLifeFilterWidget->refresh(); // Need to be in first ! Because it set filter
    mLifeListView->refresh();
    mGenePlotWidget->refresh();
    mLifePlotWidget->refresh();
    mPreviewWidget->refresh();
    mEngineView->refresh();

}






