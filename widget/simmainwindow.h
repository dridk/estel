#ifndef SIMMAINWINDOW_H
#define SIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QStringListModel>
namespace Ui {
class SimMainWindow;
}

class SimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SimMainWindow(QWidget *parent = 0);
    ~SimMainWindow();
    
private:
    Ui::SimMainWindow *ui;
    GridView * mView;
    QStringListModel * mFileModel;
    QStringListModel * mLifeModel;

};

#endif // SIMMAINWINDOW_H
