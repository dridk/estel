#include "genecolorwidget.h"

GeneColorWidget::GeneColorWidget(const Gene &gene, QWidget *parent):
    QWidget(parent)
{
    mGene = gene;
    resize(600,10);
}

void GeneColorWidget::paintEvent(QPaintEvent *)
{


    QPainter painter;
    painter.begin(this);
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(width(), 0));
    mGene.setValue(mGene.min());
    linearGrad.setColorAt(0, mGene.color());
    mGene.setValue(mGene.max());
    linearGrad.setColorAt(1, mGene.color());
    painter.setBrush(QBrush(linearGrad));
    painter.drawRect(rect());

    painter.end();



}
