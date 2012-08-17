#include "animmainwindow.h"
#include "ui_animmainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QScrollArea>
AnimMainWindow::AnimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimMainWindow)
{
    ui->setupUi(this);
    mSlider = new QSlider(Qt::Horizontal);
    mModel = new QStandardItemModel;
    mPixLabel = new QLabel;
    mTimer = new QTimer;
    QScrollArea * area = new QScrollArea;
    QVBoxLayout * layout = new QVBoxLayout;
    QWidget * widget = new QWidget;

    mTimer->setInterval(500);
    area->setWidget(mPixLabel);

    layout->addWidget(area);
    layout->addWidget(mSlider);

    widget->setLayout(layout);
    setCentralWidget(widget);

    centralWidget()->setEnabled(false);

    ui->listView->setModel(mModel);
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(addSim()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remSim()));
    connect(ui->actionMake,SIGNAL(triggered()),this,SLOT(make()));
    connect(ui->actionBackward,SIGNAL(triggered()),this,SLOT(beginPlay()));
    connect(ui->actionForward,SIGNAL(triggered()),this,SLOT(endPlay()));
    connect(ui->actionPlay,SIGNAL(triggered(bool)),this,SLOT(play(bool)));

    connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(refresh(int)));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(incrPlayerIndex()));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
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
        item->setData(filename);
        mModel->appendRow(item);
    }
}

void AnimMainWindow::remSim()
{

}

void AnimMainWindow::make()
{

    if (mModel->rowCount() <=0)
        return;
    LifeEngine * engine = new LifeEngine(100,100);
    ui->progressBar->setRange(0,mModel->rowCount()-1);
    mSlider->setRange(0,mModel->rowCount()-1);

    for (int i=0; i<mModel->rowCount(); ++i)
    {
        QString filename = mModel->item(i)->data().toString();
        if (!engine->load(filename))
        {
            qDebug()<<"cannot load "<<filename;
            break;
        }

        ui->progressBar->setValue(i);
        ui->progressBar->setFormat("Loading  simulation %v ");
        QPixmap pix = QPixmap(createPixmap(engine));
        mPixList.append(pix);
    }

    centralWidget()->setEnabled(true);
    refresh();


}
void AnimMainWindow::beginPlay()
{
    mSlider->setValue(0);
}

void AnimMainWindow::endPlay()
{
    if (!mPixList.count())
        return;
    mSlider->setValue(mPixList.count()-1);

}
void AnimMainWindow::play(bool playing)
{
    ui->actionPlay->setText(playing?"Pause":"Play");

    if (playing){
        mTimer->start();

    }
    else mTimer->stop();

}

void AnimMainWindow::refresh(int index)
{
    if (index < mPixList.count())
    {
        mPixLabel->setPixmap(mPixList.at(index));
        mPixLabel->resize(mPixList.at(index).size());
        ui->listView->setCurrentIndex (mModel->item(index)->index());

    }


}

void AnimMainWindow::incrPlayerIndex()
{

    if (mSlider->value()+1 >= mPixList.count())
    {
        mTimer->stop();
        ui->actionPlay->setChecked(false);
        mSlider->setValue(0);
        return;
    }
    mSlider->setValue(mSlider->value()+1);

}

void AnimMainWindow::itemClicked(const QModelIndex &index)
{
    int i  = index.row();
    if (i<mPixList.count())
        mSlider->setValue(i);

}
const QPixmap &AnimMainWindow::createPixmap(LifeEngine *engine)
{

    GridWidget * grid = new GridWidget(engine->rows(), engine->columns());

    foreach (Life * life, engine->lifes())
    {
        grid->switchOn(life->x(), life->y(), Qt::black);

    }

    QPixmap pix = grid->snap();
    delete grid;

    return pix;

}







