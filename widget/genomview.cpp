#include "genomview.h"

GenomView::GenomView(Life *life, QWidget *parent):
    ActionListView(parent)
{
    mLife = life;
    mModel = new QStandardItemModel;
    view()->setModel(mModel);
    connect(this,SIGNAL(doubleClicked()),this,SLOT(edit()));

    refresh();
}

void GenomView::add()
{
    GeneDialog * dialog  =new GeneDialog;
    if (dialog->exec() == QDialog::Rejected)
        return;

    mLife->addGene(dialog->gene());
    refresh();

    emit changed();

}

void GenomView::edit()
{
    if (!selectionCount())
        return;

    GeneDialog * dialog  =new GeneDialog;
    dialog->setGene(mLife->genom().genes().at(currentRow()));
    if (dialog->exec() == QDialog::Rejected)
        return;

    mLife->remGene(mLife->genom().genes().at(currentRow()));
    mLife->addGene(dialog->gene());
    refresh();
    emit changed();
}

void GenomView::remove()
{
    if (!selectionCount())
        return;

    mLife->remGene(mLife->genom().genes().at(currentRow()));

    refresh();
    emit changed();


}

void GenomView::refresh()
{
    mModel->clear();
    mModel->setHorizontalHeaderLabels(QStringList()<<"identify: "+
                                      mLife->genom().identity());

    foreach (Gene g, mLife->genom().genes())
    {
        QPixmap pix(16,16);
        pix.fill(g.rootColor());
        QStandardItem * item = new QStandardItem;
        item->setEditable(false);
        item->setIcon(QIcon(pix));
        item->setText(g.name());
        mModel->appendRow(item);
    }


}
