#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "metapolygonitem.h"

namespace Ui {
class ShapeWidget;
}

class ShapeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ShapeWidget(QWidget *parent = 0);
    ~ShapeWidget();
public slots:
    void set();
    
private:
    Ui::ShapeWidget *ui;
    MetaPolygonItem * mShape;
    QGraphicsScene * mScene;
};

#endif // SHAPEWIDGET_H
