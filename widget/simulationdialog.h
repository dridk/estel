#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include <QThread>
#include "lifeengine.h"


class SimulationThread : public QThread
{
    Q_OBJECT
public:
    SimulationThread(LifeEngine * engine);
    void setParams(int totalStep, const QString& destination);
    void run();

signals:
    void fileSaved(const QString& filename);
    void stepChanged(int step);


private:
    int mTotalStep;
    QString mDestination;
    LifeEngine * mEngine;

};


namespace Ui {
class SimulationDialog;
}

class SimulationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SimulationDialog(LifeEngine * engine, QWidget *parent = 0);
    ~SimulationDialog();
public slots:
    void run();

protected slots:
    void setDestination();
    void finished();
    
private:
    Ui::SimulationDialog *ui;
    LifeEngine * mEngine;
    SimulationThread * mThread;

};

#endif // SIMULATIONDIALOG_H
