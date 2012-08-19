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
    mLifeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    mGeneCombBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    QToolBar * toolbar = new QToolBar(this);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    toolbar->addWidget(mLifeComboBox);
    toolbar->addWidget(mGeneCombBox);
    toolbar->addWidget(spacer);
    toolbar->addAction(QIcon(":arrow_refresh.png"),"refresh",this,SLOT(refresh()));



    QVBoxLayout * layout =new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
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

    mGridView->grid()->clear();

    foreach (Life * life, mEngine->lifes())
    {
        if (life->name() == mLifeComboBox->currentText())
        {
            QString gname = mGeneCombBox->currentText();
            life->gene(gname).generateColor();
            QColor color = life->gene(gname).color();

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




