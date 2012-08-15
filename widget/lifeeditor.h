#ifndef LIFEEDITOR_H
#define LIFEEDITOR_H

#include <QMainWindow>
#include <QFile>
#include "gene.h"
#include "genedialog.h"
namespace Ui {
class LifeEditor;
}

class LifeEditor : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LifeEditor(QWidget *parent = 0);
    ~LifeEditor();

public slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNewGene_triggered();
    void on_actionEditGene_triggered();
    void on_actionRemGene_triggered();

protected:
    void refresh();

private:
    Ui::LifeEditor *ui;
    QMap<QString,Gene> mGenes;
};

#endif // LIFEEDITOR_H
