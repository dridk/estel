#include "simmainwindow.h"
#include "ui_simmainwindow.h"

SimMainWindow::SimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimMainWindow)
{
    ui->setupUi(this);
    mView = new GridView(100,100);
    mFileModel = new QStringListModel(this);
//    mLifeModel = new QStringListModel;

//ui->fileListView->setModel(mFileModel);
//ui->lifeListView->setModel(mLifeModel);

    setCentralWidget(mView);
}

SimMainWindow::~SimMainWindow()
{
    delete ui;
}
