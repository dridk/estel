#ifndef GENECOLORWIDGET_H
#define GENECOLORWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QPainter>
class ColorGradientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorGradientWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

public slots:
    void setColor(const QColor& col);

    

private:
    QColor mColor;

    
};

#endif // GENECOLORWIDGET_H
