#ifndef SIMMAINWINDOW_H
#define SIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QStringListModel>
#include <QApplication>
#include <QComboBox>
#include "lifeengine.h"
#include "lifeeditor.h"
#include "simulationdialog.h"
#include "lifeengineview.h"
#include "lifesview.h"
#include "lifefileview.h"

namespace Ui {
class SimMainWindow;
}

class SimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SimMainWindow(QWidget *parent = 0);
    ~SimMainWindow();
public slots:
    void newSim();
    void openSim();
    void saveSim();
    void saveAsSim();

    void refresh();
    void showLifeEditor();
    void startSimulation();




protected slots:
    void clicked(QPoint pos);

private:
    Ui::SimMainWindow *ui;
    LifeEngineView * mView;
    LifeEngine * mEngine;
    LifesView * mLifesView;
    LifeFileView * mLifeFileView;


};

#endif // SIMMAINWINDOW_H
