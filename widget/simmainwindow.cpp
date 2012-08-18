#include "simmainwindow.h"
#include "ui_simmainwindow.h"
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QMenu>
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
    mOldLifeCount = 0;

    ui->dock1->setWidget(mLifeFileView);
    ui->dock2->setWidget(mLifesView);

    ui->dock1->setWindowTitle(mLifeFileView->windowTitle());
    ui->dock2->setWindowTitle(mLifesView->windowTitle());

    setCentralWidget(mView);

    ui->menuLifesTypes->addActions(mLifeFileView->actions());
    ui->menuLifes->addActions(mLifesView->actions());


    connect(mView->gridView()->grid(),SIGNAL(squareClicked(QPoint)),this,SLOT(clicked(QPoint)));

    connect(ui->actionRun,SIGNAL(triggered()),this,SLOT(startSimulation()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newSim()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveSim()));
    connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAsSim()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openSim()));
    connect(ui->actionClear,SIGNAL(triggered()),this,SLOT(clear()));
    connect(ui->actionAnimator,SIGNAL(triggered()),this,SLOT(showAnimator()));
    connect(ui->actionLifeEditor,SIGNAL(triggered()),this,SLOT(showLifeEditor()));
    connect(mLifesView,SIGNAL(changed()),this,SLOT(refresh()));

    ui->actionSave->setEnabled(false);
    newSim();
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
    if (ui->actionSave->isEnabled())
    {
        QMessageBox * box = new QMessageBox;
        box->setWindowTitle("Warning");
        box->setIcon(QMessageBox::Warning);
        box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        box->setText("Do you want to save your current work ?");

        if (box->exec() == QMessageBox::Yes)
            saveSim();
    }

    clear();
    setWindowTitle("No Name");
    ui->actionSave->setEnabled(false);



}

void SimMainWindow::openSim()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open Simulation")
                                                  ,"",  tr("Estel (*.estel)"));

    if (fileName.isEmpty())
        return;
    if(!mEngine->load(fileName)){
        QMessageBox::warning(this,"error","cannot open file");
        return;
    }
    setWindowTitle(fileName);
    ui->actionSave->setEnabled(false);
    refresh();
}

void SimMainWindow::saveSim()
{
    QString fileName = windowTitle();
    if (!QFile::exists(fileName))
        fileName = QFileDialog::getSaveFileName(this,tr("Save Simulation"),
                                                "", tr("Estel Simulation (*.estel"));

    if(!mEngine->save(fileName)){
        QMessageBox::warning(this,"error","Cannot save file");
        return;
    }
    setWindowTitle(fileName);
    ui->actionSave->setEnabled(false);

}

void SimMainWindow::saveAsSim()
{

    QString fileName =QFileDialog::getSaveFileName(this,tr("Open Simulation")
                                                   ,"",  tr("Estel (*.estel)"));

    if(!mEngine->save(fileName)){
        QMessageBox::warning(this,"error","cannot save file");
        return;
    }
    setWindowTitle(fileName);
    ui->actionSave->setEnabled(false);

}
void SimMainWindow::refresh()
{
    if (mEngine->lifes().count() != mOldLifeCount)
        ui->actionSave->setEnabled(true);

    statusBar()->showMessage("Load lifes....");
    mView->refresh();
    mLifesView->refresh();
    statusBar()->showMessage("Lifes loaded");
    mOldLifeCount = mEngine->lifes().count();

}

void SimMainWindow::clear()
{
    mEngine->clear();
    refresh();
    ui->actionSave->setEnabled(true);

}

void SimMainWindow::showLifeEditor()
{
    LifeEditor * w = new LifeEditor;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();

}

void SimMainWindow::startSimulation()
{
    SimulationDialog * dialog = new SimulationDialog(mEngine);
    dialog->exec();
    refresh();
}

void SimMainWindow::showAnimator()
{
    AnimMainWindow * w = new AnimMainWindow;
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
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

