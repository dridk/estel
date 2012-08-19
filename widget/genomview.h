#ifndef GENOMVIEW_H
#define GENOMVIEW_H
#include "actionlistview.h"
#include "life.h"
#include "genedialog.h"
#include <QStandardItemModel>
class GenomView : public ActionListView
{
    Q_OBJECT
public:
    explicit GenomView(Life * life, QWidget *parent = 0);
    void setGenom(const Genom& genom);
public slots:
    void add();
    void edit();
    void remove();
    void refresh();


    
private:
    QStandardItemModel * mModel;
    Life * mLife;
    
};

#endif // GENOMVIEW_H
