#include "genedialog.h"
#include "ui_genedialog.h"
#include "genecolorwidget.h"
#include <QColorDialog>
GeneDialog::GeneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneDialog)
{
    ui->setupUi(this);
    mGeneColorWidget =  new GeneColorWidget;
    ui->varTab->layout()->addWidget(mGeneColorWidget);

    connect(ui->colorButton,SIGNAL(clicked()),this,SLOT(showColorDialog()));
}

GeneDialog::~GeneDialog()
{
    delete ui;
}

Gene GeneDialog::gene()
{
    Gene g;
    g.setName(ui->nameEdit->text());
    g.setValue(ui->valueEdit->value());
    g.setLimit(ui->minEdit->value(), ui->maxEdit->value());
    g.setVariance(ui->varianceEdit->value());
    g.setMutationProbability(ui->probaEdit->value());
    g.setRootColor(mColor);

    return g;
}

void GeneDialog::setGene(const Gene &gene)
{

    ui->nameEdit->setText(gene.name());
    ui->valueEdit->setValue(gene.value());
    ui->minEdit->setValue(gene.min());
    ui->maxEdit->setValue(gene.max());
    ui->varianceEdit->setValue(gene.variance());
    ui->probaEdit->setValue(gene.mutationProbability());
    setColor(gene.rootColor());

}

void GeneDialog::setColor(const QColor &color)
{
    mColor = color;
    QPixmap pix(32,32);
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    paint.setBrush(QColor(mColor));
    paint.setPen(QPen(Qt::transparent));
    paint.drawEllipse(QRect(3,3,24,24));
    ui->colorButton->setIcon(QIcon(pix));

    Gene currentGene = gene();
    currentGene.setRootColor(mColor);
    mGeneColorWidget->setGene(currentGene);
}

void GeneDialog::showColorDialog()
{
    QColor col = QColorDialog::getColor();
    setColor(col);
    Gene currentGene = gene();
    currentGene.setRootColor(col);
    mGeneColorWidget->setGene(currentGene);


}


