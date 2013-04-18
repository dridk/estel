/***************************************************************************
**                                                                        **
**  FcsViewer, a simple cytometry data viewer made with Qt4 and           **
**  customplot made by Emanuel Eichhammer                                 **
**  Copyright (C) 2013 Sacha Schutz                                       **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author : Sacha Schutz                                        **
**           Website: http://www.labsquare.org                            **
**           Email  : sacha@labsquare.org                                 **
**           Date   : 12.03.12                                            **
****************************************************************************/

#include "previewwidget.h"
#include <QSize>
PreviewWidget::PreviewWidget(QWidget *parent) :
    QWidget(parent)
{
    mEngineView = NULL;
    setFixedSize(256,256);

    mPix = QPixmap(size());
    mPix.fill(Qt::white);


    setWindowTitle("MiniMap");
    setWindowIcon(QIcon(":grid.png"));

    QAction * refreshAction = new QAction("refresh",this);
    connect(refreshAction,SIGNAL(triggered()),this,SLOT(refresh()));
    addAction(refreshAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);


}

void PreviewWidget::setEngineView(LifeEngineView *view)
{
    mEngineView = view;
}

void PreviewWidget::mouseMoveEvent(QMouseEvent *ev)
{
    if (mEngineView == NULL)
        return;


    int rx = mEngineView->viewport()->width()  * width() / mEngineView->widget()->width();
    int ry = mEngineView->viewport()->height() * height() / mEngineView->widget()->height();


    mZone.setRect(0,0,rx,ry);

    mZone.moveTo(ev->pos() - mZone.center());

    int ax  = (mZone.x()) * mEngineView->horizontalScrollBar()->maximum()/width();
    int ay  = (mZone.y()) * mEngineView->verticalScrollBar()->maximum()/height();


    mEngineView->horizontalScrollBar()->setValue(ax);
    mEngineView->verticalScrollBar()->setValue(ay);

    repaint();



}

void PreviewWidget::paintEvent(QPaintEvent * event)
{

    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),mPix.scaled(size()));

    painter.setPen(QPen(Qt::lightGray));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0,0,size().width()-1, size().height()-1);

    painter.setBrush(QBrush(QColor(255,255,0,50)));
    painter.drawRect(mZone);


}

void PreviewWidget::refresh()
{
    if (mEngineView == NULL)
        return;

    mPix = QPixmap(mEngineView->engine()->rows(), mEngineView->engine()->columns());
    mPix.fill(Qt::white);
    QPainter painter(&mPix);

    foreach (Life * life, mEngineView->engine()->lifes())
    {

        if (mEngineView->lifeFilter().contains(life->name())) {


            QColor col = Qt::black;
            foreach (Gene gene, life->genom().genes())
            {
                if (mEngineView->geneFilter().contains(gene.name()))
                    col = gene.color();
            }


            painter.setPen(QPen(col));
            painter.drawPoint(life->x(),life->y());

        }
    }

    repaint();
}
