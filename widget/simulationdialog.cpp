#include "simulationdialog.h"
#include "ui_simulationdialog.h"

SimulationDialog::SimulationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationDialog)
{
    ui->setupUi(this);
}

SimulationDialog::~SimulationDialog()
{
    delete ui;
}
