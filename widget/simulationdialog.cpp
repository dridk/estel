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
//        ui->timeLabel->setText(time.toString("mm:ss:zzz"));
        ui->sizeLabel->setText(QString::number(sizeof(Life) * mEngine->population()));


        mEngine->step();
        ++i;
        ui->progressBar->setValue(i);

    }
    ui->pushButton->setEnabled(true);



}
