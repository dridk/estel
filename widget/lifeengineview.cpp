#include "lifeengineview.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
LifeEngineView::LifeEngineView(QWidget *parent):
    GridView(500,500,parent)
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
    setGridSize(engine->rows(),engine->columns());
    connect(mEngine,SIGNAL(changed()),this,SLOT(refresh()));
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

        if (mLifeFilter.contains(life->name()))
        {
            QColor col = Qt::black;

            foreach (Gene gene, life->genom().genes())
            {
                if (mGeneFilter.contains(gene.name()))
                    col = gene.color();
            }
            switchOn(life->x(),life->y(), col);
        }


    }

    gridWidget()->repaint();
}

void LifeEngineView::setLifeFilter(const QStringList &names)
{
    mLifeFilter = names;
}
void LifeEngineView::setGeneFilter(const QStringList &names)
{
    mGeneFilter = names;
}
void LifeEngineView::selectLife(const QPoint &pos)
{
    qDebug()<<pos;
    selectOn(pos.x(),pos.y());

}

