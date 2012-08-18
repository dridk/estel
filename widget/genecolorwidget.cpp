#include "genecolorwidget.h"

GeneColorWidget::GeneColorWidget(const Gene &gene, QWidget *parent):
    QWidget(parent)
{
    mGene = gene;
    resize(600,10);
}

void GeneColorWidget::paintEvent(QPaintEvent *)
{



}
