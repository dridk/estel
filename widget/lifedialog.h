#ifndef LIFEDIALOG_H
#define LIFEDIALOG_H

#include <QDialog>
#include "life.h"
namespace Ui {
class LifeDialog;
}

class LifeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LifeDialog(Life * life,QWidget *parent = 0);
    ~LifeDialog();

protected slots:
    void load();
    void save();
    
private:
    Ui::LifeDialog *ui;
    Life * mLife;
};

#endif // LIFEDIALOG_H
