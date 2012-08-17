#ifndef LIFESVIEW_H
#define LIFESVIEW_H
#include "actionlistview.h"
#include "lifeengine.h"
#include <QStandardItemModel>
#include "lifedialog.h"
class LifesView : public ActionListView
{
    Q_OBJECT
public:
    explicit LifesView(LifeEngine * engine,QWidget *parent = 0);

    void refresh();
    void remove();
    void edit();

    


private:
    LifeEngine * mEngine;
    QStandardItemModel * mModel;
    
};

#endif // LIFESVIEW_H
