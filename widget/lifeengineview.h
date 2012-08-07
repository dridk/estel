#ifndef LIFEENGINEVIEW_H
#define LIFEENGINEVIEW_H

#include <QWidget>
#include "lifeengine.h"
#include "gridview.h"


class LifeEngineView : public QWidget
{
    Q_OBJECT
public:
    explicit LifeEngineView(LifeEngine * engine, QWidget *parent = 0);
    ~LifeEngineView();

public slots:
    void load() ;
    void loadGeneList();
    void loadFile();

private:
    LifeEngine * mEngine;
    GridView * mGridView;
    QLabel * mPopLabel;
    QComboBox * mComboBox;
    QSlider * mSlider;
    
};

#endif // LIFEENGINEVIEW_H
