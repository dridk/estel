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
    mView = new GridView(mEngine->rows(),mEngine->columns());
    mFileModel = new QStringListModel(this);
    mLifeModel = new QStringListModel(this);
    mLifeTypeCombo  = new QComboBox;
    mGeneCombo = new QComboBox;

    ui->fileListView->setModel(mFileModel);
    ui->lifeListView->setModel(mLifeModel);

    setCentralWidget(mView);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->toolBar2->addWidget(spacer);
    ui->toolBar2->addWidget(mLifeTypeCombo);
    ui->toolBar2->addWidget(mGeneCombo);

    connect(mView->grid(),SIGNAL(squareClicked(QPoint)),this,SLOT(clicked(QPoint)));
    connect(mLifeTypeCombo,SIGNAL(activated(int)),this,SLOT(updateGeneCombo()));
    connect(mLifeTypeCombo,SIGNAL(activated(int)),this,SLOT(updateGrid()));
    connect(mGeneCombo,SIGNAL(activated(int)),this,SLOT(updateGrid()));

    connect(ui->fileListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(showLifeEditor()));
    connect(ui->actionRun,SIGNAL(triggered()),this,SLOT(startSimulation()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveSim()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openSim()));

    connect(ui->actionEditLife,SIGNAL(triggered()),this,SLOT(editLife()));
    connect(ui->actionRemLife,SIGNAL(triggered()),this,SLOT(remLife()));

    updateLifeFile();

}

SimMainWindow::~SimMainWindow()
{
    delete ui;
    delete mEngine;
    delete mView;
    delete mLifeTypeCombo;
    delete mGeneCombo;

}

void SimMainWindow::newSim()
{
}

void SimMainWindow::openSim()
{
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Open Simulation"), "", tr("Estel Simulation (*.estel"));

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

void SimMainWindow::updateLifeFile(const QString &path)
{
    QString currentDir = path;
    if ( path.isEmpty())
        currentDir = qApp->applicationDirPath();

    QStringList filters;
    filters << "*.json"<<"*.life";

    QDir dir(currentDir);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(filters);

    QStringList list;
    foreach (QFileInfo fileInfo, dir.entryInfoList())
        list.append(fileInfo.fileName());

    mFileModel->setStringList(list);

}

void SimMainWindow::updateLifeList()
{
    QStringList list;
    foreach (Life * life, mEngine->lifes())
    {
        QString data = life->name();
        data.append(life->genom().identity());
        list.append(data);
    }
    mLifeModel->setStringList(list);
    updateCombo();

}

void SimMainWindow::refresh()
{
    updateLifeList();
    updateGrid();
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
    if ( ui->lifeListView->selectionModel()->selectedRows().count() <=0)
        return;

    int row = ui->lifeListView->selectionModel()->selectedRows().first().row();

    Life * life = mEngine->lifes().value(row);

    LifeDialog * dialog = new LifeDialog(life);
    dialog->exec();

    updateGrid();


}

void SimMainWindow::remLife()
{
    if ( ui->lifeListView->selectionModel()->selectedRows().count() <=0)
        return;

    foreach (QModelIndex index, ui->lifeListView->selectionModel()->selectedRows())
    {
        QPoint pos = mEngine->lifes().value(index.row())->pos();
        mEngine->remLife(pos.x(),pos.y());
    }

    updateLifeList();
    updateGrid();





}

void SimMainWindow::updateGrid()
{
    qDebug()<<"update grid";
    mView->grid()->clear();
    QString currentType = mLifeTypeCombo->currentText();
    QString currentGene = mGeneCombo->currentText();


    foreach (Life * life, mEngine->lifes())
    {
        if (life->name() == currentType)
        {

            mView->grid()->switchOn(life->x(),life->y(),
                                    life->gene(currentGene).color());

        }

        if ( currentType == "all")
            mView->grid()->switchOn(life->x(),life->y(),Qt::black);
    }
    mView->grid()->update();
}

void SimMainWindow::updateCombo()
{
    QStringList names;
    mLifeTypeCombo->clear();
    mLifeTypeCombo->addItem("all");
    foreach (Life * life, mEngine->lifes())
    {
        if (!names.contains(life->name()))
            names.append(life->name());

    }
    mLifeTypeCombo->addItems(names);
    updateGeneCombo();
}

void SimMainWindow::updateGeneCombo()
{
    Life * lifeTemp = new Life;
    if ( mLifeTypeCombo->currentText()=="all")
        mGeneCombo->setEnabled(false);
    else mGeneCombo->setEnabled(true);
    lifeTemp->loadFile(mLifeTypeCombo->currentText()+".json");


    mGeneCombo->clear();
    foreach (Gene gene, lifeTemp->genom().genes())
        mGeneCombo->addItem(gene.name());


}

void SimMainWindow::clicked(QPoint pos)
{
    if (mEngine->hasLife(pos.x(),pos.y()))
        return;

    if (ui->fileListView->selectionModel()->selectedIndexes().count() <= 0)
        return;

    QString fileName = mFileModel->stringList().at(
                ui->fileListView->selectionModel()->selectedRows().first().row());

    Life * life = new Life;
    //====== load file....
    if (!life->loadFile(fileName))
    {
        delete life;
        qDebug()<<"cannot load life file...";
        return;
    }
    //====== Test if position is avaible....

    if (mEngine->hasLife(pos.x(),pos.y()))
    {
        delete life;
        qDebug()<<"cannot add life on this position";
        return;
    }

    life->setPos(pos);
    life->setAge(0);
    mEngine->addLife(life);

    refresh();
}
