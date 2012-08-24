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
    connect(this,SIGNAL(doubleClicked()),this,SLOT(edit()));

    actions().at(1)->setText("Edit current life");
    actions().at(2)->setText("Remove current life");
    actions().at(3)->setText("Refresh lifes list");


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

    Life * life = mEngine->lifes().at(currentRow());
    LifeDialog * dialog = new LifeDialog(life);
    dialog->exec();

}
