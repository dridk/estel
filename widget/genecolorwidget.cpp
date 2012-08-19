#include "genecolorwidget.h"
#include <QDebug>
GeneColorWidget::GeneColorWidget(QWidget *parent):
    QWidget(parent)
{
    setMinimumHeight(10);


}

void GeneColorWidget::paintEvent(QPaintEvent *)
{

    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::transparent));
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(width(), 0));
    mGene.setValue(mGene.min());
    linearGrad.setColorAt(0, mGene.color());
    mGene.setValue(mGene.max());
    linearGrad.setColorAt(1, mGene.color());
    painter.setBrush(QBrush(linearGrad));
    painter.drawRect(rect());

    painter.end();



}

void GeneColorWidget::setGene(const Gene &gene)
{
    mGene = gene;
    update();
}
