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
    void newFile();
    void openFile(const QString& name = QString());
    void saveFile();
    void saveAs();
    void addGene();
    void remGene();
    void editGene();
    void reset();
    void step();



    void canBeSaved(bool enable = true);

protected:
    void refresh();

private:
    Ui::LifeEditor *ui;
    Genom mGenes;
    LifeEngine * mEngine;
    Life * mCurrentLife;
    int mCurrentStep;
};

#endif // LIFEEDITOR_H
