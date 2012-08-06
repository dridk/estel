#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    void loadData(QVector<int> datas);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);

protected:
    void createGraph();
    
private:
    QVector<int> mDatas;
    QPainterPath mPath;
    QPixmap mGraph;
    QRect mSurface;
    int mXCursor;
    int mMaxX, mMaxY;
    int mGridDivision;
    
};

#endif // GRAPHWIDGET_H
