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
    mLifeComboBox->setObjectName("localCombo");
    mGeneCombBox->setObjectName("localCombo");

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
    connect(mLifeComboBox,SIGNAL(activated(int)),this,SLOT(refresh()));
    connect(mGeneCombBox,SIGNAL(activated(int)),this,SLOT(refresh()));


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
    bool updateCombo = true;
    if (sender())
    {
        if (sender()->objectName() == "localCombo"){
            updateCombo = false;
        }
    }

    if (updateCombo)
        mComboData.clear();

    foreach (Life * life, mEngine->lifes())
    {
        if (life->name() == mLifeComboBox->currentText())
        {
            QColor color = life->gene(mGeneCombBox->currentText()).color();
            mGridView->grid()->switchOn(life->x(),life->y(),color);
        }
        else
            mGridView->grid()->switchOn(life->x(),life->y(),Qt::black);

        if (updateCombo)
            mComboData[life->name()] = life->genom();


    }

    mGridView->grid()->update();
    if (updateCombo)
        updateLifeCombo();
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




