#include "simulationdialog.h"
#include "ui_simulationdialog.h"
#include <QDateTime>
SimulationDialog::SimulationDialog(LifeEngine *engine, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SimulationDialog)
{
    ui->setupUi(this);
    mEngine = engine;

    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(run()));
}

SimulationDialog::~SimulationDialog()
{
    delete ui;
}

void SimulationDialog::run()
{
    int totalStep = ui->spinBox->value();
    int i = 0;
    QDateTime beginTime = QDateTime::currentDateTime();
    ui->progressBar->setRange(0,totalStep);
    ui->pushButton->setEnabled(false);


    while (i<totalStep)
    {
        QDateTime time;
        time.fromTime_t(beginTime.toTime_t()-QDateTime::currentDateTime().toTime_t());

        ui->popLabel->setText(QString::number(mEngine->population()));
        ui->sizeLabel->setText(QString::number(sizeof(Life) * mEngine->population()));
        mEngine->step();

        QString filename=beginTime.toString("MMyy-hhmm")
                +QString::number(i)+".estel";

        if(mEngine->save(filename))
            ui->plainTextEdit->appendPlainText(filename+" saved");

        ++i;
        ui->progressBar->setValue(i);

    }
    ui->pushButton->setEnabled(true);



}
