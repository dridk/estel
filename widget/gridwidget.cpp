#include "gridwidget.h"
#include <QDebug>

GridWidget::GridWidget(int row, int column, QWidget *parent):
    QWidget(parent)
{
    mSquareSize = 10;
    mColumnCount = column;
    mRowCount = row ;


    //    setMinimumSize(mSquareSize*mRowCount, mSquareSize * mColumnCount);
    //    setMaximumSize(mSquareSize*mRowCount, mSquareSize * mColumnCount);

    setFixedSize(mSquareSize*mRowCount, mSquareSize * mColumnCount);

    createGrid();


}

void GridWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint;
    paint.begin(this);

    paint.drawPixmap(0,0,mGridPix);


    foreach (int index , mColors.keys())
    {

        int y = qRound(index/mColumnCount);
        int x = index % mRowCount;

        paint.setBrush(mColors[index]);
        paint.drawRect(x*mSquareSize,y*mSquareSize, mSquareSize, mSquareSize);



    }


    paint.end();



}

void GridWidget::mousePressEvent(QMouseEvent * event)
{

    int X = event->x() / mSquareSize;
    int Y = event->y() / mSquareSize;

    qDebug()<<"press"<<X<<" "<<Y;
    switchOn(X,Y, Qt::blue);

    update(QRegion(X*mSquareSize,Y*mSquareSize,mSquareSize,mSquareSize));

}

void GridWidget::switchOn(int x, int y, const QColor &color)
{

    int index =  mColumnCount * y  + x;
    mColors[index] = color;


}

void GridWidget::switchOff(int x, int y)
{
    int index =  mColumnCount * y  + x;
    mColors.remove(index);

}


void GridWidget::createGrid()
{

    mGridPix = QPixmap(size());
    mGridPix.fill(Qt::white);
    QPainter paint(&mGridPix);
    paint.setPen(QPen(Qt::lightGray));


    for ( int x=0;x<width();x+=mSquareSize )
        paint.drawLine(x,rect().top(), x, rect().bottom());

    for ( int y=0;y<height();y+=mSquareSize )
        paint.drawLine(rect().left(),y,rect().right(),y);


























}
