#include "genedialog.h"
#include "ui_genedialog.h"

GeneDialog::GeneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneDialog)
{
    ui->setupUi(this);
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

    return g;
}
