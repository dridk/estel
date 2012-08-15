#ifndef SIMMAINWINDOW_H
#define SIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QStringListModel>
#include <QApplication>
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
    
private:
    Ui::SimMainWindow *ui;
    GridView * mView;
    QStringListModel * mFileModel;
    QStringListModel * mLifeModel;

};

#endif // SIMMAINWINDOW_H
