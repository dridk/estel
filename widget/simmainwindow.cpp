#include "simmainwindow.h"
#include "ui_simmainwindow.h"
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include "lifedialog.h"
SimMainWindow::SimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimMainWindow)
{
    ui->setupUi(this);
    mEngine = new LifeEngine(100,100);
    mView = new LifeEngineView(mEngine);
    mLifeFileView = new LifeFileView;
    mLifesView = new LifesView(mEngine);


    ui->dock1->setWidget(mLifeFileView);
    ui->dock2->setWidget(mLifesView);

    ui->dock1->setWindowTitle(mLifeFileView->windowTitle());
    ui->dock2->setWindowTitle(mLifesView->windowTitle());

    setCentralWidget(mView);


    connect(mView->gridView()->grid(),SIGNAL(squareClicked(QPoint)),this,SLOT(clicked(QPoint)));

    //    connect(ui->fileListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showLifeEditor()));
    connect(ui->actionRun,SIGNAL(triggered()),this,SLOT(startSimulation()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveSim()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openSim()));

    connect(ui->actionEditLife,SIGNAL(triggered()),this,SLOT(editLife()));
    connect(ui->actionRemLife,SIGNAL(triggered()),this,SLOT(remLife()));
}

SimMainWindow::~SimMainWindow()
{
    delete ui;
    delete mEngine;
    delete mView;
    delete mLifesView;
    delete mLifeFileView;

}

void SimMainWindow::newSim()
{
}

void SimMainWindow::openSim()
{
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Open Simulation"), "",  tr("Estel (*.estel)"));

    if(mEngine->load(fileName)){
        setWindowTitle(fileName);
        refresh();
    }

    else qDebug()<<"cannot open simulation";
}

void SimMainWindow::saveSim()
{
    QString fileName = windowTitle();
    if (!QFile::exists(windowTitle()))
    {
        fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save Simulation"), "", tr("Estel Simulation (*.estel"));
    }

    if(mEngine->save(fileName))
        setWindowTitle(fileName);
    else qDebug()<<"Cannot save Simulation";

}
void SimMainWindow::refresh()
{
    mView->refresh();
    mLifesView->refresh();
}

void SimMainWindow::showLifeEditor()
{
    LifeEditor * editor = new LifeEditor;


    //    editor->setWindowModality(Qt::ApplicationModal);
    editor->show();
    //    editor->set
    //    connect(editor, SIGNAL(destroyed()), &loop, SLOT(quit()));
    //    loop.exec();

    //    qDebug()<<"end";


}

void SimMainWindow::startSimulation()
{
    SimulationDialog * dialog = new SimulationDialog(mEngine);
    dialog->exec();
    refresh();
}

void SimMainWindow::editLife()
{
    //    if ( ui->lifeListView->selectionModel()->selectedRows().count() <=0)
    //        return;

    //    int row = ui->lifeListView->selectionModel()->selectedRows().first().row();

    //    Life * life = mEngine->lifes().value(row);

    //    LifeDialog * dialog = new LifeDialog(life);
    //    dialog->exec();

    //    refresh();
}

void SimMainWindow::remLife()
{
    //    if ( ui->lifeListView->selectionModel()->selectedRows().count() <=0)
    //        return;

    //    foreach (QModelIndex index, ui->lifeListView->selectionModel()->selectedRows())
    //    {
    //        QPoint pos = mEngine->lifes().value(index.row())->pos();
    //        mEngine->remLife(pos.x(),pos.y());
    //    }

    //    refresh();
}

void SimMainWindow::clicked(QPoint pos)
{
    if (mEngine->hasLife(pos.x(),pos.y()))
        return;

    if (!mLifeFileView->selectionCount())
        return;

    if (mEngine->hasLife(pos.x(),pos.y()))
        return;

    QString filename = mLifeFileView->currentFilename();

    qDebug()<<filename;
    Life * life = Life::fromFile(filename);
    if (!life)
        return;

    life->setPos(pos);
    life->setAge(0);
    mEngine->addLife(life);

    refresh();
}
