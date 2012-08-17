#ifndef ANIMMAINWINDOW_H
#define ANIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QSplitter>
#include <QStringList>
namespace Ui {
class AnimMainWindow;
}

class AnimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AnimMainWindow(QWidget *parent = 0);
    ~AnimMainWindow();

public slots:
    void addSim();
    void remSim();
    void make();

    void beginPlay();
    void endPlay();
    void play(bool playing = true);


    
private:
    Ui::AnimMainWindow *ui;
    GridView * mView;
    QSlider * mSlider;
QStandardItemModel * mModel;
};

#endif // ANIMMAINWINDOW_H
