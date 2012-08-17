#ifndef ANIMMAINWINDOW_H
#define ANIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QSplitter>
namespace Ui {
class AnimMainWindow;
}

class AnimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AnimMainWindow(QWidget *parent = 0);
    ~AnimMainWindow();
    
private:
    Ui::AnimMainWindow *ui;
    GridView * mView;
    QSlider * mSlider;
};

#endif // ANIMMAINWINDOW_H
