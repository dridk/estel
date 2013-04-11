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
    void addFilter(const QString& lifeName, const QString& geneName);
    void remFilter(const QString& lifeName);
    void clearFilter();


protected slots:
    void selectLife(const QPoint& pos);


private:
    LifeEngine * mEngine;
    QHash<QString, QString> mGenesFilter;


    
};

#endif // LIFEENGINEVIEW_H
