#ifndef ANIMMAINWINDOW_H
#define ANIMMAINWINDOW_H

#include <QMainWindow>
#include "gridview.h"
#include <QSplitter>
#include <QStringList>
#include <QPixmap>
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
    void clear();

    void beginPlay();
    void endPlay();
    void play(bool playing = true);
    void refresh(int index = 0);

protected slots:
    void incrPlayerIndex();
    void itemClicked(const QModelIndex& index);
    void loadComboData();
    void loadComboGeneData();



protected:
     QPixmap * createPixmap(LifeEngine * engine);
private:
    Ui::AnimMainWindow *ui;
    QSlider * mSlider;
    QLabel * mPixLabel;
    QStringListModel * mModel;
    QList<QString> mPixList;
    QTimer * mTimer;
    QMap<QString, Genom> mComboData;
};

#endif // ANIMMAINWINDOW_H
