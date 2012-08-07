#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QtGui>
#include "gridwidget.h"

class GridView : public QScrollArea
{
    Q_OBJECT
public:
    explicit GridView(int row, int column,QWidget *parent = 0);
    ~GridView();
    GridWidget * grid() ;
    
private:
    GridWidget * mGridWidget;
    
};

#endif // GRIDVIEW_H
