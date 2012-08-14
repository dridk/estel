#ifndef GENEDIALOG_H
#define GENEDIALOG_H

#include <QDialog>
#include "gene.h"
namespace Ui {
class GeneDialog;
}

class GeneDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GeneDialog(QWidget *parent = 0);
    ~GeneDialog();
     Gene gene() ;
    
private:
    Ui::GeneDialog *ui;
};

#endif // GENEDIALOG_H
