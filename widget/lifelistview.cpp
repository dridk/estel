#include "lifelistview.h"
#include <QDebug>
LifeListView::LifeListView(QWidget *parent) :
    ActionListView(parent)
{
    mEngine = NULL;
    mModel = new QStandardItemModel;
    mModel->setColumnCount(2);

    view()->setModel(mModel);
    setWindowTitle("Lifes");


}

void LifeListView::refresh()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    mModel->clear();
    foreach ( Life * life, mEngine->lifes())
    {
        QList<QStandardItem*> items;
        QStandardItem * item =new QStandardItem();
        item->setEditable(false);
        item->setText(life->name());
        item->setIcon(QIcon(":dna"));


        QStandardItem * item2 =new QStandardItem();
        item2->setEditable(false);
        item2->setText(life->genom().identity());
        items.append(item);
        items.append(item2);
        mModel->appendRow(items);
    }

    showMessage(QString::number(mEngine->lifes().count()));
    emit changed();
}

void LifeListView::add()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    LifeDialog * dialog = new LifeDialog;

    if (dialog->exec() == QDialog::Rejected)
        return;

    Life * life = new Life(dialog->life());

    mEngine->addLife(life);

    refresh();

}

void LifeListView::remove()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    QList<Life*> lifes;

    qDebug()<<"count"<<view()->selectionModel()->selectedRows().count();

    foreach (QModelIndex  i, view()->selectionModel()->selectedRows())
        lifes.append(mEngine->lifes().at(i.row()));

    foreach (Life * life, lifes)
        mEngine->remLife(life);

    refresh();
}

void LifeListView::edit()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    if (view()->selectionModel()->selectedIndexes().count())
    {
        int row = view()->selectionModel()->selectedIndexes().first().row();
        Life * life = mEngine->lifes().at(row);
        LifeDialog * dialog = new LifeDialog;
        dialog->setLife(*life);
        if (dialog->exec() == QDialog::Rejected)
            return;

        *life = dialog->life();
    }

    refresh();

}

void LifeListView::setEngine(LifeEngine *engine)
{
    mEngine = engine;
    refresh();
}