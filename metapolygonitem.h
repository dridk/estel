#ifndef METAPOLYGONITEM_H
#define METAPOLYGONITEM_H

#include <QGraphicsItem>

class MetaPolygonItem : public QGraphicsItem
{
public:
    MetaPolygonItem(QGraphicsItem * parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    void setShape(int count, int radius);

private:
    QPolygon mPolygon;
    int mVertexCount;
    int mRadius;
};

#endif // METAPOLYGONITEM_H
