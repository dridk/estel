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
    explicit GridWidget(int row, int column,QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void switchOn(int x,int y, const QColor& color);
    void switchOff(int x, int y);
    void clear();




protected:
    void createGrid();



private:
    int mSquareSize;
    int mRowCount;
    int mColumnCount;
    QPixmap mGridPix;
    QHash<int, QColor >mColors;



    
};

#endif // GRIDWIDGET_H
