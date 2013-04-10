#ifndef LIFEDIALOG_H
#define LIFEDIALOG_H

#include <QDialog>
#include <QtGui>
#include "life.h"
#include "genomview.h"

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
    Life * mLife;
    QSpinBox * mAgeSpinBox;
    QLineEdit * mNameEdit;
    QSpinBox * mXSpinBox;
    QSpinBox * mYSpinBox;
    GenomView * mGenomView;
};

#endif // LIFEDIALOG_H
