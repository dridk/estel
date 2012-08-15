#ifndef LIFEEDITOR_H
#define LIFEEDITOR_H

#include <QMainWindow>
#include <QFile>
#include "lifeengine.h"
#include "gene.h"
#include "life.h"
#include "genom.h"
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
    void on_actionSimReset_triggered();
    void on_actionSimStep_triggered();

    void canBeSaved(bool enable = true);

protected:
    void refresh();

private:
    Ui::LifeEditor *ui;
    Genom mGenes;
    LifeEngine * mEngine;
};

#endif // LIFEEDITOR_H
