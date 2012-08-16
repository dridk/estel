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

    connect(mLifeComboBox,SIGNAL(activated(int)),this,SLOT(updateGeneCombo()));


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
        if (life->name() == mLifeComboBox->currentText())
        {
            QColor color = life->gene(mGeneCombBox->currentText()).color();
            mGridView->grid()->switchOn(life->x(),life->y(),color);
        }
        else
            mGridView->grid()->switchOn(life->x(),life->y(),Qt::black);
    }

    mGridView->grid()->update();
    updateComboData();
}

GridView *LifeEngineView::gridView()
{
    return mGridView;
}

void LifeEngineView::updateLifeCombo()
{

    mLifeComboBox->clear();
    mLifeComboBox->addItem("All");
    mLifeComboBox->addItems(mComboData.keys());
}

void LifeEngineView::updateGeneCombo()
{
    mGeneCombBox->clear();
    if (mLifeComboBox->currentText() == "All")
        mGeneCombBox->setEnabled(false);
    else mGeneCombBox->setEnabled(true);

    foreach (Gene gene, mComboData[mLifeComboBox->currentText()].genes())
        mGeneCombBox->addItem(gene.name());
}

void LifeEngineView::updateComboData()
{
    mComboData.clear();
    foreach (Life * life, mEngine->lifes())
        mComboData[life->name()] = life->genom();


}


