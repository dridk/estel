#include "metapolygonitem.h"
#include <QPainter>
#include <cmath>
#include <QDebug>
MetaPolygonItem::MetaPolygonItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    setShape(4, 5);
}

void MetaPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(QBrush(Qt::red));
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawPolygon(mPolygon);

//    painter->setBrush(QBrush(QColor(255,255,0,40)));
//    painter->drawRect(boundingRect());


}


QRectF MetaPolygonItem::boundingRect()const
{
   QRect rect = mPolygon.boundingRect();
   rect.adjust(-50,-50,50,50);
   return rect;
}

void MetaPolygonItem::setShape(int count, int radius)
{

    mPolygon.clear();
    double step = 360 / count/2;
    for (int i=0; i<count; ++i)
    {

        double a = double(i) * 360 / double(count);
        double x =  cos(a*M_PI/180)*50;
        double y =  sin(a*M_PI/180)*50;

        double a2 = (a+step);
        double x2 =  cos(a2*M_PI/180)*radius;
        double y2 =  sin(a2*M_PI/180)*radius;


        mPolygon.append(QPoint(x,y));
        mPolygon.append(QPoint(x2 ,y2));


    }
    qDebug()<<mPolygon;
    update();




}
