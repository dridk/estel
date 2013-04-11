#include "genomview.h"
#include <QPainter>
GenomView::GenomView( QWidget *parent):
    ActionListView(parent)
{
    mModel = new QStandardItemModel;
    view()->setModel(mModel);

}

void GenomView::setGenom(const Genom &genom)
{
    mGenom = genom;
    refresh();
}

const Genom &GenomView::genom() const
{
    return mGenom;
}

void GenomView::add()
{
    GeneDialog * dialog  =new GeneDialog;
    if (dialog->exec() == QDialog::Rejected)
        return;

    Gene gene = dialog->gene();
    mGenom.append(gene);
    delete dialog;

    refresh();

}

void GenomView::edit()
{
    if (!selectionCount())
        return;

    GeneDialog * dialog  =new GeneDialog;
    Gene oldGene = mGenom.genes().at(currentRow());
    dialog->setGene(oldGene);
    if (dialog->exec() == QDialog::Rejected)
        return;

    Gene gene = dialog->gene();
    if (gene.name() != oldGene.name())
        mGenom.remove(oldGene.name());

    mGenom[gene.name()] = gene;

    refresh();
}

void GenomView::remove()
{
    QList<QString> names;

    qDebug()<<"count"<<view()->selectionModel()->selectedRows().count();

    foreach (QModelIndex index, view()->selectionModel()->selectedRows())
        names.append(mGenom.genes().at(index.row()).name());

    foreach (QString name, names)
       mGenom.remove(name);



    refresh();


}

void GenomView::refresh()
{
    mModel->clear();

    foreach (Gene g, mGenom.genes())
    {
        QPixmap pix(16,16);
        pix.fill(Qt::transparent);
        QPainter paint(&pix);
        paint.setRenderHint(QPainter::Antialiasing,true);
        paint.setBrush(QBrush(g.color()));
        paint.setPen(Qt::NoPen);
        paint.drawEllipse(QRectF(0,0,15,15));
        QStandardItem * item = new QStandardItem;
        item->setEditable(false);
        item->setIcon(QIcon(pix));
        item->setText(QString("%1 : %2").arg(g.name()).arg(g.value()));
        item->setToolTip(QString("[%1-%2] v:%3 p:%4").arg(g.min()).arg(g.max())
                         .arg(g.variance()).arg(g.mutationProbability()));
        mModel->appendRow(item);
    }


}
