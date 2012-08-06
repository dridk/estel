#include "genomwidget.h"
#include <QDebug>
#include <QToolTip>
GenomWidget::GenomWidget(const Genom &genom, QWidget *parent):
    QWidget(parent)
{

    mGenom = genom;
    setMinimumHeight(20);
    setMaximumHeight(20);
    createRects();

}

void GenomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);

    int i = 0;
    foreach ( QRect rect , mRects)

    {
        painter.setBrush(QBrush(mGenom.gene(i)->color()));
        painter.setPen(QPen(Qt::white));
        painter.drawRect(rect);
        ++i;
    }
}

void GenomWidget::mousePressEvent(QMouseEvent *event)
{


    int index = 0;
    foreach ( QRect rect , mRects)
    {

        if (rect.contains(event->pos())){
           QString info;
           info+= "name  : "+mGenom.gene(index)->name()+"\n";
           info+= "value : "+QString::number(mGenom.gene(index)->value())+"\n";
           info+= "limit : ["+QString::number(mGenom.gene(index)->min())+"-"+QString::number(mGenom.gene(index)->max())+ "]\n";
           info+= "proba : "+QString::number(mGenom.gene(index)->mutationProbability())+ "\n";
           info+= "odds : "+QString::number(mGenom.gene(index)->variance())+ "\n";


            QToolTip::showText(event->globalPos(), info);


        }



        index++;
    }


}

void GenomWidget::resizeEvent(QResizeEvent *)
{
    createRects();
}

void GenomWidget::createRects()
{
    mRects.clear();

    double tt = mGenom.count(); // = width


    int lastX = 0;
    for ( int i=0; i<mGenom.count(); ++i)
    {

        int w =   width() / tt;
        QRect rect(lastX,0,w,height());
        lastX = lastX + w;
        mRects.append(rect);
    }
}
