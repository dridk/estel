#ifndef LIFEDIALOG_H
#define LIFEDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QDialogButtonBox>
#include "life.h"
#include "genomview.h"

class LifeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LifeDialog(QWidget *parent = 0);
    ~LifeDialog();

    void setLife(const Life& life);
    const Life& life();

    
private:
    Life mLife;
    QSpinBox * mAgeSpinBox;
    QLineEdit * mNameEdit;
    QSpinBox * mXSpinBox;
    QSpinBox * mYSpinBox;
    GenomView * mGenomView;
    QDialogButtonBox * mDialogBox;
};

#endif // LIFEDIALOG_H
