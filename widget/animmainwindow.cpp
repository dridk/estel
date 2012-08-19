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
    ui->controlToolBar->setEnabled(false);


    ui->listView->setModel(mModel);
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(addSim()));
    connect(ui->actionRemove,SIGNAL(triggered()),this,SLOT(remSim()));
    connect(ui->actionMake,SIGNAL(triggered()),this,SLOT(make()));
    connect(ui->actionBackward,SIGNAL(triggered()),this,SLOT(beginPlay()));
    connect(ui->actionForward,SIGNAL(triggered()),this,SLOT(endPlay()));
    connect(ui->actionPlay,SIGNAL(triggered(bool)),this,SLOT(play(bool)));
    connect(ui->actionClear,SIGNAL(triggered()),this,SLOT(clear()));
    connect(ui->lifeTypeCombo,SIGNAL(currentIndexChanged(int)),this,SLOT(loadComboGeneData()));

    connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(refresh(int)));
    connect(mTimer,SIGNAL(timeout()),this,SLOT(incrPlayerIndex()));
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));



}


AnimMainWindow::~AnimMainWindow()
{
    delete ui;
    delete mSlider;
    delete mPixLabel;
    delete mModel;
    delete mTimer;
    mPixList.clear();
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

    loadComboData();
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
    mPixList.clear();

    QFileInfo info(mModel->item(0)->data().toString());
    QDir dir(info.path());
    dir.mkdir("cache");
    dir.cd("cache");


    qDebug()<<"cache path"<<dir.path();

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
        QFileInfo info(filename);
        QString pixFile = dir.path()+
                QDir::separator()+info.baseName()+".png";
        QPixmap * pix  = createPixmap(engine);
        pix->save(pixFile);
        delete pix;
        mPixList.append(pixFile);
    }

    centralWidget()->setEnabled(true);
    ui->controlToolBar->setEnabled(true);

    refresh();


}

void AnimMainWindow::clear()
{
    mModel->clear();
    mPixList.clear();
    mPixLabel->setPixmap(QPixmap());
    centralWidget()->setEnabled(false);
    ui->controlToolBar->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->geneCombo->clear();
    ui->lifeTypeCombo->clear();



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
        QPixmap pix = QPixmap(mPixList.at(index));
        mPixLabel->setPixmap(pix);
        mPixLabel->resize(pix.size());
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


void AnimMainWindow::loadComboData()
{
    if (mModel->rowCount()<=0)
        return;

    QString fileName = mModel->item(0)->data().toString();
    LifeEngine * engine = new LifeEngine(100,100);
    if(engine->load(fileName))
    {
        foreach (Life * life, engine->lifes())
            mComboData[life->name()] = life->genom();

        ui->lifeTypeCombo->clear();
        ui->lifeTypeCombo->addItem("All");
        ui->lifeTypeCombo->addItems(mComboData.keys());

    }



}

void AnimMainWindow::loadComboGeneData()
{
    if (!ui->lifeTypeCombo->currentIndex())
    {
        ui->geneCombo->setEnabled(false);
        return;
    }

    ui->geneCombo->setEnabled(true);
    ui->geneCombo->clear();
    QString key = ui->lifeTypeCombo->currentText();
    foreach (Gene gene, mComboData[key].genes())
        ui->geneCombo->addItem(gene.name());




}

QPixmap * AnimMainWindow::createPixmap(LifeEngine *engine)
{
    GridWidget * grid = new GridWidget(engine->rows(), engine->columns());

    foreach (Life * life, engine->lifes())
    {
        if (!ui->lifeTypeCombo->currentIndex())
            grid->switchOn(life->x(), life->y(), Qt::black);

        if (life->name() == ui->lifeTypeCombo->currentText())
        {
            QString gname = ui->geneCombo->currentText();
            QColor col = life->gene(gname).color();
            grid->switchOn(life->x(), life->y(), col);
        }

    }

    QPixmap * result =  grid->snap();
    delete grid;

    return result;



}







