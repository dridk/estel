#include "graphwidget.h"
#include <QDebug>
GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent)
{
    mGridDivision = 4;
    mXCursor = 0;

}

void GraphWidget::loadData(QVector<int> datas)
{


    mDatas = datas;
    if (mDatas.isEmpty())
        return;

    int index = 0 ;
    foreach ( int value, mDatas)
    {

        mMaxX = qMax(mMaxX, value);
        mMaxY = qMax(mMaxY,index);



        ++index;
    }

    qDebug()<<mMaxX<<" "<<mMaxY;
    createGraph();
    repaint();
}

void GraphWidget::paintEvent(QPaintEvent *)
{

    if (mDatas.isEmpty())
        return;

    QPainter painter;
    painter.begin(this);

    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(mSurface);

    painter.drawLine(mSurface.bottomLeft(),mSurface.bottomRight());
    painter.drawLine(mSurface.bottomLeft(),mSurface.topLeft());


    painter.setPen(QPen(Qt::lightGray));
    for ( int x = mSurface.left() +mSurface.width()/mGridDivision ; x<mSurface.right() - mSurface.width()/mGridDivision; x+= mSurface.width()/mGridDivision)
        painter.drawLine(x,mSurface.bottom(),x,mSurface.top());


    for ( int y = mSurface.top()+ mSurface.height()/mGridDivision; y<mSurface.bottom()- mSurface.height()/mGridDivision; y+= mSurface.height()/mGridDivision)
        painter.drawLine(mSurface.left(),y,mSurface.right(),y);



    painter.drawPixmap(mSurface.x(),mSurface.y(),mGraph);


    painter.setPen(QPen(Qt::blue));

    painter.drawLine(mXCursor, mSurface.bottom(), mXCursor, mSurface.top());

//    painter.drawText(x,10,QString::number(mDatas[mXCursor]));



    painter.end();
}

void GraphWidget::resizeEvent(QResizeEvent *)
{
    mSurface = rect();
    mSurface.adjust(10,10,-10,-10);
    createGraph();

}

void GraphWidget::mouseMoveEvent(QMouseEvent *event)
{

    int x = qBound(mSurface.left(),event->x(),mSurface.right());

    mXCursor = x;
    repaint();
    QWidget::mouseMoveEvent(event);

}



void GraphWidget::createGraph()
{

    mGraph = QPixmap(mSurface.size());
    mGraph.fill(Qt::transparent);

    QPainter paint(&mGraph);
    QPainterPath path;
    path.moveTo(mSurface.bottomLeft());
    int index = 0;
    foreach ( int value, mDatas)
    {


        qDebug()<<index<<" "<<value;
        int cx = index * mSurface.width() / mMaxX;
        int cy = value *mSurface.height() / mMaxY;


        qDebug()<<value<<"*"<<mSurface.height()<<"/"<<mMaxY<<" = "<<cy;

        cy = mSurface.height() - cy;


        index++;
        path.lineTo(cx,cy);
        path.addRect(cx,cy,10,10);



    }

    paint.setPen(QPen(Qt::black));
    paint.setBrush(Qt::NoBrush);

    paint.drawPath(path);
}


