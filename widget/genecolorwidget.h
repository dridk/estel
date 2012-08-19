#ifndef GENECOLORWIDGET_H
#define GENECOLORWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QPainter>
#include "gene.h"
class GeneColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GeneColorWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

    void setGene(const Gene& gene);
    

private:
    Gene mGene;

    
};

#endif // GENECOLORWIDGET_H
