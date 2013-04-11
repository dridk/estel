#include "colorgradientwidget.h"
#include <QDebug>
ColorGradientWidget::ColorGradientWidget(QWidget *parent):
    QWidget(parent)
{
    setMinimumHeight(10);
    mColor = Qt::red;

}

void ColorGradientWidget::paintEvent(QPaintEvent *)
{

    QPainter painter;
    painter.begin(this);
    painter.setPen(QPen(Qt::transparent));
    QLinearGradient linearGrad(QPointF(0, 0), QPointF(width(), 0));
    linearGrad.setColorAt(1, mColor);
    linearGrad.setColorAt(0, Qt::black);
    painter.setBrush(QBrush(linearGrad));
    painter.drawRect(rect());

    painter.end();



}

void ColorGradientWidget::setColor(const QColor &col)
{
    mColor = col;
    repaint();
}
