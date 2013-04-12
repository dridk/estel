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

     QList<Life*> lifeSelected() const;


public slots:
    void refresh();
    void setLifeFilter(const QStringList& names);
    void setGeneFilter(const QStringList& names);



protected slots:
    void selectLife(const QPoint& pos);


private:
    LifeEngine * mEngine;
    QStringList mLifeFilter;
    QStringList mGeneFilter;


    
};

#endif // LIFEENGINEVIEW_H
