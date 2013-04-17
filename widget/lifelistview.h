#ifndef LIFESVIEW_H
#define LIFESVIEW_H
#include "actionlistview.h"
#include "lifeengine.h"
#include <QStandardItemModel>
#include "lifedialog.h"
#include "lifeeditorwindow.h"
class LifeListView : public ActionListView
{
    Q_OBJECT
public:
    explicit LifeListView(QWidget *parent = 0);

    void refresh();
    void add();
    void remove();
    void edit();

    void setEngine(LifeEngine * engine);

private:
    LifeEngine * mEngine;
    QStandardItemModel * mModel;
    
};

#endif // LIFESVIEW_H
