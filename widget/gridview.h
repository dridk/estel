#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QtGui>
#include "gridwidget.h"

class GridView : public QWidget
{
    Q_OBJECT
public:
    explicit GridView(QWidget *parent = 0);
    ~GridView();
    
private:
    GridWidget * mGridWidget;
    QScrollArea * mArea;
    QComboBox * mComboBox;
    QToolBar * mToolBar;
    
};

#endif // GRIDVIEW_H
