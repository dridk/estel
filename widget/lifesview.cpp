#include "lifesview.h"
#include <QDebug>
LifesView::LifesView(LifeEngine *engine, QWidget *parent) :
    ActionListView(parent)
{
    mEngine = engine;
    mModel = new QStandardItemModel;
    mModel->setColumnCount(2);

    view()->setModel(mModel);
    refresh();
    setWindowTitle("Lifes");


}

void LifesView::refresh()
{
    mModel->clear();

    mModel->setHorizontalHeaderLabels(QStringList()<<"name"<<"genom");

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

void LifesView::remove()
{

    foreach (QModelIndex  i, view()->selectionModel()->selectedRows())
    {
        Life * life = mEngine->lifes().at(i.row());
        mEngine->remLife(life->x(),life->y());
    }
    refresh();
    emit changed();
}

void LifesView::edit()
{
    if (!selectionCount())
        return;

//    Life * life = mEngine->lifes().at(currentRow());
//    LifeDialog * dialog = new LifeDialog(life);
//    dialog->exec();

}
