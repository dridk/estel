#ifndef LIFEEDITOR_H
#define LIFEEDITOR_H

#include <QMainWindow>
#include <QFile>
#include "lifeengine.h"
#include "gene.h"
#include "life.h"
#include "genom.h"
#include "genedialog.h"
#include "genomview.h"
#include "jsonmodel.h"
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
    void reset();
    void step();


protected slots:
    void workHasChanged();



private:
    Ui::LifeEditor *ui;
    Genom mGenes;
    LifeEngine * mEngine;
    GenomView * mGenomView;
    JsonModel * mJsonModel;

    Life * mCurrentLife;
    int mCurrentStep;
};

#endif // LIFEEDITOR_H
