#include "animmainwindow.h"
#include "ui_animmainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
AnimMainWindow::AnimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimMainWindow)
{
    ui->setupUi(this);
    mView = new GridView(100,100);
    mSlider = new QSlider(Qt::Horizontal);
    mModel = new QStandardItemModel;
    QVBoxLayout * layout = new QVBoxLayout;
    QWidget * widget = new QWidget;
    layout->addWidget(mView);
    layout->addWidget(mSlider);

    widget->setLayout(layout);
    setCentralWidget(widget);

    ui->listView->setModel(mModel);
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(addSim()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remSim()));
    connect(ui->actionMake,SIGNAL(triggered()),this,SLOT(make()));
    connect(ui->actionBackward,SIGNAL(triggered()),this,SLOT(beginPlay()));
    connect(ui->actionForward,SIGNAL(triggered()),this,SLOT(endPlay()));
    connect(ui->actionPlay,SIGNAL(triggered(bool)),this,SLOT(play(bool)));

}

AnimMainWindow::~AnimMainWindow()
{
    delete ui;
}

void AnimMainWindow::addSim()
{

    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                          "get simulations",
                                                          "",
                                                          "(*.estel)"
                                                          );

    foreach (QString filename, filenames)
    {

        QFileInfo info(filename);
        QStandardItem * item =new QStandardItem;
        item->setEditable(false);
        item->setText(info.baseName());
        item->setIcon(QIcon(":layer.png"));
        mModel->appendRow(item);


    }









}

void AnimMainWindow::remSim()
{
}

void AnimMainWindow::make()
{
}

void AnimMainWindow::beginPlay()
{
}

void AnimMainWindow::endPlay()
{

}
void AnimMainWindow::play(bool playing)
{

}
