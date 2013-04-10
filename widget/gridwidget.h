#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QGenericMatrix>
#include <QMouseEvent>

#include "life.h"



class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(int rowCount = 100, int columnCount =100,QWidget *parent = 0);
    void setGridSize(int rowCount, int columnCount);
    void switchOn(int x,int y, const QColor& color);
    void switchOff(int x, int y);
    void selectOn(int x,int y);
    void selectOff(int x,int y);
    void clear();
    void clearSelection();
    void setCellSize(int size);
     QPixmap * snap() ;

protected:
    void drawGrid(QPaintDevice * device);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);



protected:
    void createGrid();

signals:
    void cellClicked(QPoint pos);


private:
    int mCellSize;
    int mRowCount;
    int mColumnCount;
    QPixmap mGridPix;
    QHash<int, QColor >mColors;
    QList<int> mCellSelected;



    
};

#endif // GRIDWIDGET_H
