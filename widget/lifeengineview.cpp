#include "lifeengineview.h"
#include <QToolBar>
#include <QVBoxLayout>
LifeEngineView::LifeEngineView(LifeEngine *engine, QWidget *parent):
    QWidget(parent)
{
    mEngine = engine;
    mGridView = new GridView(engine->rows(),engine->columns());
    mLifeComboBox = new QComboBox;
    mGeneCombBox = new QComboBox;

    QToolBar * toolbar = new QToolBar(this);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    toolbar->addWidget(spacer);
    toolbar->addWidget(mLifeComboBox);
    toolbar->addWidget(mGeneCombBox);


    QVBoxLayout * layout =new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(mGridView);

    setLayout(layout);


    refresh();

}

LifeEngineView::~LifeEngineView()
{
    delete mGridView;
    delete mLifeComboBox;
    delete mGeneCombBox;



}

void LifeEngineView::refresh()
{

    foreach (Life * life, mEngine->lifes())
    {
        mGridView->grid()->switchOn(life->x(),life->y(),Qt::black);
        mComboData[life->name()] = life->genom();
    }




}

void LifeEngineView::updateLifeCombo()
{

}

void LifeEngineView::updateGeneCombo()
{

}


