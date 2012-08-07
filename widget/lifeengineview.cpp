#include "lifeengineview.h"
#include <QToolBar>
#include <QVBoxLayout>
LifeEngineView::LifeEngineView(LifeEngine *engine, QWidget *parent):
    QWidget(parent)
{
    mEngine = engine;
    mGridView = new GridView(100,100);
    mPopLabel = new QLabel;
    mComboBox = new QComboBox;
    mSlider = new QSlider(Qt::Horizontal);
    mSlider->setRange(0,500);
    QToolBar * toolbar = new QToolBar(this);

    toolbar->addWidget(mComboBox);
    toolbar->addSeparator();
    toolbar->addWidget(mPopLabel);
    toolbar->addWidget(mSlider);


    QVBoxLayout * layout =new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(mGridView);

    setLayout(layout);


    mPopLabel->setText("Population "+QString::number(engine->population()));

    loadGeneList();
    load();

    connect(mComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(load()));
    connect(mSlider,SIGNAL(valueChanged(int)),this,SLOT(loadFile()));

}

LifeEngineView::~LifeEngineView()
{
    delete mGridView;
    delete mPopLabel;
    delete mComboBox;


}

void LifeEngineView::load()
{
    mGridView->grid()->clear();


    QString currentGene = mComboBox->currentText();


    foreach ( Life * life, mEngine->lifes())
    {


        mGridView->grid()->switchOn(life->x(),life->y(),life->gene(currentGene).color());



    }

    mGridView->grid()->repaint();
}

void LifeEngineView::loadGeneList()
{
    if (!mEngine->population())
        return;


    mComboBox->clear();

    foreach (Gene gene, mEngine->lifes().first()->genom().genes())
        mComboBox->addItem(gene.name());






}

void LifeEngineView::loadFile()
{
    mEngine->load("experimentA-"+QString::number(mSlider->value())+".json");
    load();

}
