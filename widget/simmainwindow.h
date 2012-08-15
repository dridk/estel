#ifndef SIMMAINWINDOW_H
#define SIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QStringListModel>
#include <QApplication>
#include "lifeengine.h"
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
    void loadLifeFile(const QString& path = QString());
    void loadLife();

protected slots:
    void clicked(QPoint pos);
    
private:
    Ui::SimMainWindow *ui;
    GridView * mView;
    QStringListModel * mFileModel;
    QStringListModel * mLifeModel;
    LifeEngine * mEngine;

};

#endif // SIMMAINWINDOW_H
