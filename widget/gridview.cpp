#include "gridview.h"
#include <QVBoxLayout>
#include <QToolBar>
GridView::GridView(QWidget *parent) :
    QWidget(parent)
{

    mGridWidget = new GridWidget(100,100);
    mArea  = new QScrollArea;
    mToolBar = new QToolBar;
    mComboBox = new QComboBox;


    mToolBar->addWidget(mComboBox);

    mArea->setWidget(mGridWidget);

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(mToolBar);
    layout->addWidget(mArea);

    setLayout(layout);

    mGridWidget->switchOn(10,20,Qt::red);


}

GridView::~GridView()
{
    delete mArea;
    delete mToolBar;
    delete mGridWidget;
    delete mComboBox;

}
