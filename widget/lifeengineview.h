#ifndef LIFEENGINEVIEW_H
#define LIFEENGINEVIEW_H

#include <QWidget>
#include "lifeengine.h"
#include "gridview.h"

class LifeEngineView : public GridView
{
    Q_OBJECT
public:
    explicit LifeEngineView( QWidget *parent = 0);
    ~LifeEngineView();
    void setEngine(LifeEngine * engine);
    LifeEngine * engine();
     QList<Life*> lifeSelected() ;




public slots:
    void refresh();




protected slots:
    void selectLife(const QPoint& pos);


private:
    LifeEngine * mEngine;




    
};

#endif // LIFEENGINEVIEW_H
