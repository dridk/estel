#include "simmainwindow.h"
#include "ui_simmainwindow.h"
#include <QDir>
#include <QDebug>
SimMainWindow::SimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimMainWindow)
{
    ui->setupUi(this);
    mEngine = new LifeEngine(100,100);
    mView = new GridView(mEngine->rows(),mEngine->columns());
    mFileModel = new QStringListModel(this);
    mLifeModel = new QStringListModel(this);

    ui->fileListView->setModel(mFileModel);
    ui->lifeListView->setModel(mLifeModel);

    setCentralWidget(mView);

    connect(mView->grid(),SIGNAL(squareClicked(QPoint)),this,SLOT(clicked(QPoint)));

    loadLifeFile();

}

SimMainWindow::~SimMainWindow()
{
    delete ui;
}

void SimMainWindow::loadLifeFile(const QString &path)
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

void SimMainWindow::loadLife()
{
    QStringList list;
    foreach (Life * life, mEngine->lifes())
    {
        QString data = life->name();
        data.append(life->genom().identity());
        list.append(data);
    }
    mLifeModel->setStringList(list);
}

void SimMainWindow::clicked(QPoint pos)
{
    if (mEngine->hasLife(pos.x(),pos.y()))
        return;

    Life * life = new Life(pos.x(),pos.y());

    mEngine->addLife(life);

    if (mEngine->hasLife(pos.x(),pos.y())){
    mView->grid()->switchOn(pos.x(),pos.y(),Qt::black);
    mView->grid()->update();
    loadLife();
   }



    loadLife();


}
