#ifndef GENEDIALOG_H
#define GENEDIALOG_H

#include <QDialog>
#include "gene.h"
#include "genecolorwidget.h"
namespace Ui {
class GeneDialog;
}

class GeneDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GeneDialog(QWidget *parent = 0);
    ~GeneDialog();
    Gene gene() ;
    void setGene(const Gene& gene);
public slots:
    void setColor(const QColor& color);
    void showColorDialog();
    
private:
    Ui::GeneDialog *ui;
    Gene mGene;
    QColor mColor;
    GeneColorWidget * mGeneColorWidget;
};

#endif // GENEDIALOG_H
