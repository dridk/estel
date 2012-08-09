#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>

namespace Ui {
class SimulationDialog;
}

class SimulationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SimulationDialog(QWidget *parent = 0);
    ~SimulationDialog();
    
private:
    Ui::SimulationDialog *ui;
};

#endif // SIMULATIONDIALOG_H
