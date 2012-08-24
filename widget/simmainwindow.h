#ifndef SIMMAINWINDOW_H
#define SIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QStringListModel>
#include <QApplication>
#include <QComboBox>
#include <QUndoStack>
#include "lifeengine.h"
#include "lifeeditor.h"
#include "simulationdialog.h"
#include "lifeengineview.h"
#include "lifesview.h"
#include "lifefileview.h"
#include "animmainwindow.h"
namespace Ui {
class SimMainWindow;
}

class SimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SimMainWindow(QWidget *parent = 0);
    ~SimMainWindow();
    LifeEngine * engine()const;
    LifeEngineView * view() const;
public slots:
    void newSim();
    void openSim();
    void saveSim();
    void saveAsSim();

    void refresh();
    void clear();
    void startSimulation();

    void showAnimator();
    void showLifeEditor();

    void showAboutQt();
    void showAbout();



protected slots:
    void clicked(QPoint pos);
    void setGridSelection();


private:
    Ui::SimMainWindow *ui;
    LifeEngineView * mView;
    LifeEngine * mEngine;
    LifesView * mLifesView;
    LifeFileView * mLifeFileView;
    QUndoStack * mUndoStack;
    int mOldLifeCount;


};

#endif // SIMMAINWINDOW_H
