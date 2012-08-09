#include "lifetypewidget.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QAction>
LifeTypeWidget::LifeTypeWidget(QWidget *parent) :
    QWidget(parent)
{

    mListWidget = new QListWidget;
    QToolBar * toolbar = new QToolBar;

    QAction * addAction = toolbar->addAction("Add");

    QVBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(toolbar);
    layout->addWidget(mListWidget);

    setLayout(layout);

}

void LifeTypeWidget::addLife(const Life &life)
{

    mLifes.append(life);

}
