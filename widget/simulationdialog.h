#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include "lifeengine.h"
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
    void setDestination();
    
private:
    Ui::SimulationDialog *ui;
    LifeEngine * mEngine;
    QString mDestination;
};

#endif // SIMULATIONDIALOG_H
