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
    void refresh();

protected slots:
    void updateLifeCombo();
    void updateGeneCombo();


private:
    LifeEngine * mEngine;
    GridView * mGridView;
    QComboBox * mLifeComboBox;
    QComboBox * mGeneCombBox;
    QMap<QString, Genom> mComboData;

    
};

#endif // LIFEENGINEVIEW_H
