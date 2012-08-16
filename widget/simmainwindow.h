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

    void refresh();
    void showLifeEditor();
    void startSimulation();
    void editLife();
    void remLife();



protected slots:
    void clicked(QPoint pos);
    void updateLifeFile(const QString& path = QString());
    void updateLifeList();

private:
    Ui::SimMainWindow *ui;
    LifeEngineView * mView;
    QStringListModel * mFileModel;
    QStringListModel * mLifeModel;
    LifeEngine * mEngine;


};

#endif // SIMMAINWINDOW_H
