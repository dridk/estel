#include "simmainwindow.h"
#include "ui_simmainwindow.h"
#include <QDir>
#include <QDebug>
SimMainWindow::SimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimMainWindow)
{
    ui->setupUi(this);
    mView = new GridView(100,100);
    mFileModel = new QStringListModel(this);
    mLifeModel = new QStringListModel(this);

    ui->fileListView->setModel(mFileModel);
    ui->lifeListView->setModel(mLifeModel);

    setCentralWidget(mView);

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
