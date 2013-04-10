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

     QList<Life*> lifeSelected() const;


public slots:
    void refresh();
    void setLifeFilter(const QString& lifeName);
    void setGeneFilter(const QString& geneName);

protected slots:
    void selectLife(const QPoint& pos);


private:
    LifeEngine * mEngine;
    QString mCurrentLifeName;
    QString mCurrentGeneName;


    
};

#endif // LIFEENGINEVIEW_H
