#include "simulationdialog.h"
#include "ui_simulationdialog.h"
#include <QDateTime>
#include <QApplication>
#include <QFileDialog>

//============== SIMULATION THREAD ==============
SimulationThread::SimulationThread(LifeEngine *engine)
{
    mEngine = engine;
}



void SimulationThread::setParams(int totalStep, const QString &destination)
{
    mTotalStep = totalStep;
    mDestination = destination;
}

void SimulationThread::run()
{
    int i = 0;
    QDateTime beginTime = QDateTime::currentDateTime();
    while (i<mTotalStep)
    {
        QDateTime time;
        time.fromTime_t(beginTime.toTime_t()-QDateTime::currentDateTime().toTime_t());

        mEngine->step();

        QString filename= "sim_"+QString::number(i)+".estel";
        filename = mDestination+QDir::separator()+filename;

        if(!mEngine->save(filename))
            qDebug()<<"cannot save...";

        qDebug()<<filename<<" saved";
        ++i;
        emit fileSaved(filename);
        emit stepChanged(i);

    }
}
//============== SIMULATION Dialog ==============

SimulationDialog::SimulationDialog(LifeEngine *engine, QWidget *parent):
    QDialog(parent),
    ui(new Ui::SimulationDialog)
{
    ui->setupUi(this);
    mEngine = engine;
    mThread = new SimulationThread(engine);

    setWindowTitle("Simulation Player");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(run()));
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(setDestination()));
    connect(mThread,SIGNAL(finished()),this,SLOT(finished()));
    connect(mThread,SIGNAL(fileSaved(QString)),
            ui->plainTextEdit,SLOT(appendPlainText(QString)));
    connect(mThread,SIGNAL(stepChanged(int)),
            ui->progressBar,SLOT(setValue(int)));
    connect(ui->stopButton,SIGNAL(clicked()),mThread,SLOT(terminate()));

    ui->lineEdit->setText(qApp->applicationDirPath());
}

SimulationDialog::~SimulationDialog()
{
    delete ui;
    delete mThread;
}

void SimulationDialog::run()
{
    ui->pushButton->setEnabled(false);
    ui->progressBar->setRange(0,ui->spinBox->value());

    mThread->setParams(ui->spinBox->value(), ui->lineEdit->text());
    mThread->run();





}

void SimulationDialog::setDestination()
{

    QString destination =
            QFileDialog::getExistingDirectory(this,
                                              "error",
                                              qApp->applicationDirPath());


    ui->lineEdit->setText(destination);


}

void SimulationDialog::finished()
{
    ui->pushButton->setEnabled(false);
}

