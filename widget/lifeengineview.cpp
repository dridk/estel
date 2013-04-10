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
        if (life->name() == mCurrentLifeName || mCurrentLifeName.isEmpty())
        {
            QColor col = Qt::black;
            if (life->genom().contains(mCurrentGeneName))
                col = life->gene(mCurrentGeneName).color();

            switchOn(life->x(),life->y(), col);

        }
    }
}

void LifeEngineView::setLifeFilter(const QString &lifeName)
{
    mCurrentLifeName = lifeName;

}

void LifeEngineView::setGeneFilter(const QString &geneName)
{
    mCurrentGeneName = geneName;
}

void LifeEngineView::selectLife(const QPoint &pos)
{
    qDebug()<<pos;
    selectOn(pos.x(),pos.y());

}
