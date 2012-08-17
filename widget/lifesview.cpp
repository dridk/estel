#include "lifesview.h"
#include <QDebug>
LifesView::LifesView(LifeEngine *engine, QWidget *parent) :
    ActionListView(parent)
{
    mEngine = engine;
    mModel = new QStandardItemModel;
    view()->setModel(mModel);
    mModel->setColumnCount(2);
    refresh();
    setWindowTitle("Lifes");
    hideAction(0);
}

void LifesView::refresh()
{
    mModel->clear();

    mModel->setHorizontalHeaderLabels(QStringList()<<"name"<<"genom");



    qDebug()<<"add"<<mEngine->lifes().count();

    foreach ( Life * life, mEngine->lifes())
    {
        QList<QStandardItem*> items;
        QStandardItem * item =new QStandardItem();
        item->setEditable(false);
        item->setText(life->name());
        item->setIcon(QIcon(":molecule.png"));

        QStandardItem * item2 =new QStandardItem();
        item2->setEditable(false);
        item2->setText(life->genom().identity());


        items.append(item);
        items.append(item2);
        mModel->appendRow(items);



    }
    showMessage(QString::number(mEngine->lifes().count()));



}
