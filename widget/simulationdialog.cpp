#include "simulationdialog.h"
#include "ui_simulationdialog.h"
#include <QDateTime>
#include <QApplication>
#include <QFileDialog>
SimulationDialog::SimulationDialog(LifeEngine *engine, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SimulationDialog)
{
    ui->setupUi(this);
    mEngine = engine;

    setWindowTitle("Simulation Player");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(setDestination()));

    ui->lineEdit->setText(qApp->applicationDirPath());


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

        QString filename= "sim_"+QString::number(i)+".estel";

        filename = ui->lineEdit->text()+QDir::separator()+filename;

        qDebug()<<filename;

        if(mEngine->save(filename))
            ui->plainTextEdit->appendPlainText(filename+" saved");



        ++i;
        ui->progressBar->setValue(i);

    }
    ui->pushButton->setEnabled(true);



}

void SimulationDialog::setDestination()
{

    mDestination =
            QFileDialog::getExistingDirectory(this,
                                              "error",
                                              qApp->applicationDirPath());


    ui->lineEdit->setText(mDestination);


}
