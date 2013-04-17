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
        item->setText(life->name() +"-"+ life->genom().identity());
        item->setIcon(QIcon(":dna"));

        QStandardItem * item2 =new QStandardItem();
        item2->setEditable(false);
        item2->setText(life->genom().identity());
        items.append(item);
        items.append(item2);
        mModel->appendRow(items);
    }

    showMessage(QString::number(mEngine->lifes().count()));
}

void LifeListView::add()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    LifeEditorWindow * dialog = new LifeEditorWindow;

    if (dialog->exec() == QDialog::Rejected)
        return;

    Life * life = new Life(dialog->life());
    mEngine->addLife(life);

    emit changed();


}

void LifeListView::remove()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    QList<Life*> lifes;


    foreach (QModelIndex  i, view()->selectionModel()->selectedRows())
        lifes.append(mEngine->lifes().at(i.row()));


    qDebug()<<lifes.count()<<" a suppr";
    qDebug()<<mEngine->count();



    foreach (Life * life, lifes) {
        mEngine->remLife(life);

    }


    refresh();
  //  emit changed();

}

void LifeListView::edit()
{
    Q_ASSERT_X (mEngine != NULL,"LifeListView", "No engine set");

    if (view()->selectionModel()->selectedIndexes().count())
    {
        int row = view()->selectionModel()->selectedIndexes().first().row();
        Life * life = mEngine->lifes()[row];
        LifeEditorWindow * dialog = new LifeEditorWindow;

        dialog->setLife(Life(*life));
        if (dialog->exec() == QDialog::Rejected)
            return;

        life->clone(dialog->life());



    }

    emit changed();
   // refresh();


}

void LifeListView::setEngine(LifeEngine *engine)
{
    mEngine = engine;
    refresh();

    connect(this,SIGNAL(changed()),mEngine,SIGNAL(changed()));
    connect(mEngine,SIGNAL(changed()),this,SLOT(refresh()));

}
