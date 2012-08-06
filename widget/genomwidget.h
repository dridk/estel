#ifndef GENOMWIDGET_H
#define GENOMWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "genom.h"
class GenomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenomWidget(const Genom& genom,QWidget *parent = 0);
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *);
    
protected:
    void createRects();

private:
    Genom mGenom;
    QList<QRect> mRects;
    
};

#endif // GENOMWIDGET_H
