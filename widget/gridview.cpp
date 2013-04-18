/***************************************************************************
**                                                                        **
**  GridView, a simple GridView made with Qt4                             **
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
#include "gridview.h"
#include <QVBoxLayout>
#include <QToolBar>

GridWidget::GridWidget(int rowCount, int columnCount, QWidget *parent):
    QWidget(parent)
{

    mCellSize = 10;
    mRowCount = rowCount;
    mColumnCount = columnCount;
    mSelectorSize = 1;
    createGrid();
    setMinimumSize(1000,1000);
    switchOn(63,2,Qt::black);


}

void GridWidget::setGridSize(int rowCount, int columnCount)
{
    mRowCount = rowCount;
    mColumnCount = columnCount;

    createGrid();
}

void GridWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    drawGrid(this);
}

void GridWidget::mousePressEvent(QMouseEvent * event)
{
    int X = event->x() / mCellSize;
    int Y = event->y() / mCellSize;

    QPoint pos = QPoint(X,Y);

    if (event->modifiers() != Qt::ControlModifier)
        clearSelection();

//    for (int y=pos.y()-mSelectorSize; y<pos.y() + mSelectorSize ; ++y)
//    {
//        for (int x= pos.x()-mSelectorSize; x<pos.x() + mSelectorSize ; ++x)
//        {

            mSelection.append(pos);
//        }
//    }

    emit cellClicked(pos);
    QWidget::mousePressEvent(event);
    update();

}

void GridWidget::mouseMoveEvent(QMouseEvent * event)
{
    Q_UNUSED(event);

}

void GridWidget::switchOn(int x, int y, const QColor &color)
{

    int index =  mColumnCount * y  + x;
    mColors[index] = color;


}

void GridWidget::switchOff(int x, int y)
{
    int index =  mColumnCount * y  + x;
    mColors.remove(index);

}

void GridWidget::selectOn(int x, int y)
{


}

void GridWidget::selectOff(int x, int y)
{
}

void GridWidget::clear()
{
    mColors.clear();
}

void GridWidget::clearSelection()
{
    mSelection.clear();
}

void GridWidget::setCellSize(int size)
{
    mCellSize = size;
}

void GridWidget::showGrid(bool show)
{
    mShowGrid = show;
    repaint();
}

QPixmap * GridWidget::snap()
{
    QPixmap * pix = new QPixmap(size());
    drawGrid(pix);
    return pix;
}


void GridWidget::drawGrid(QPaintDevice *device)
{

    QPainter paint;
    paint.begin(device);
    mGridPix.fill(Qt::white);
    if (mShowGrid)
    paint.drawPixmap(0,0,mGridPix);
    //Draw Square
    foreach (int index , mColors.keys())
    {
        int y = qRound(index/mColumnCount);
        int x = index % mRowCount;

        paint.setBrush(mColors[index]);
        paint.drawRect(x*mCellSize,y*mCellSize, mCellSize, mCellSize);
    }

    //Draw SquareSelector
    foreach (QPoint pos, mSelection)
    {

        paint.setBrush(Qt::transparent);
        paint.setBrush(QBrush(Qt::Dense4Pattern));
        QRect selector = QRect(pos.x()*mCellSize,pos.y()*mCellSize, mCellSize, mCellSize);
        //selector.adjust(-2,-2,2,2);
        paint.drawRect(selector);

    }

    paint.end();

}


void GridWidget::createGrid()
{
    resize(mRowCount*mCellSize, mColumnCount*mCellSize);
    setFixedSize(size());
    mGridPix = QPixmap(size());
    mGridPix.fill(Qt::white);
    QPainter paint(&mGridPix);
    paint.setPen(QPen(Qt::lightGray));

    for ( int x=0;x<width();x+=mCellSize )
        paint.drawLine(x,rect().top(), x, rect().bottom());

    for ( int y=0;y<height();y+=mCellSize )
        paint.drawLine(rect().left(),y,rect().right(),y);


    update();


}

//================= Grid View
GridView::GridView(int row, int column, QWidget *parent):
    QScrollArea(parent)
{
    mGridWidget = new GridWidget(row,column);
    setWidget(mGridWidget);
    connect(mGridWidget,SIGNAL(cellClicked(QPoint)),this,SIGNAL(cellClicked(QPoint)));
}

GridView::~GridView()
{
    delete mGridWidget;
}


