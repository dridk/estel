#include "lifeengineview.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
LifeEngineView::LifeEngineView(QWidget *parent):
    GridView(100,100,parent)
{
    mEngine = NULL;

    QAction * action = new QAction("refresh",this);
    addAction(action);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    connect(action,SIGNAL(triggered()),this,SLOT(refresh()));
    connect(this,SIGNAL(cellClicked(QPoint)),this,SLOT(selectLife(QPoint)));

}

LifeEngineView::~LifeEngineView()
{

}
void LifeEngineView::setEngine(LifeEngine *engine)
{
    mEngine = engine;
    refresh();
}

LifeEngine *LifeEngineView::engine()
{
    return mEngine;
}

QList<Life *> LifeEngineView::lifeSelected() const
{
    Q_ASSERT_X(mEngine !=NULL, "LifeEngineView::lifeSelected", "no lifeEngine set");
    QList<Life*> lifes;

    if (mEngine == NULL)
        return lifes;

    foreach (QPoint pos, selection())
    {
        Life * life = mEngine->life(pos.x(),pos.y());
        if (life != NULL)
            lifes.append(life);
    }

    return lifes;


}

void LifeEngineView::refresh()
{
    if (mEngine == NULL)
        return;
    clear();
    foreach (Life * life, mEngine->lifes())
    {

        if (mGenesFilter.contains(life->name()))
        {
            QColor col = Qt::black;
            QString geneName = mGenesFilter[life->name()];
            if (life->genom().contains(geneName))
                col = life->gene(geneName).color();

            switchOn(life->x(),life->y(), col);


        }


    }

    gridWidget()->repaint();
}

void LifeEngineView::addFilter(const QString &lifeName, const QString &geneName)
{
    mGenesFilter[lifeName] = geneName;
}


void LifeEngineView::clearFilter()
{
    mGenesFilter.clear();
}

void LifeEngineView::remFilter(const QString &lifeName)
{
    mGenesFilter.remove(lifeName);
}

void LifeEngineView::selectLife(const QPoint &pos)
{
    qDebug()<<pos;
    selectOn(pos.x(),pos.y());

}

