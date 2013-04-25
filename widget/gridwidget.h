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

#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QtWidgets>

class GridWidget;
class GridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridWidget(int rowCount = 100, int columnCount =100,QWidget *parent = 0);
    void setGridSize(int rowCount, int columnCount);
    void switchOn(int x,int y, const QColor& color);
    void switchOff(int x, int y);
    void selectOn(int x,int y);
    void selectOff(int x,int y);
    void clear();
    void clearSelection();
    void setCellSize(int size);

    QPixmap * snap() ;

    const QList<QPoint>& selection() const {return mSelection;}

protected:
    void drawGrid(QPaintDevice * device);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);

protected:
    void createGrid();

signals:
    void cellClicked(QPoint pos);

public slots:
    void showGrid(bool show);



private:
    int mCellSize;
    int mRowCount;
    int mColumnCount;
    QPixmap mGridPix;
    QHash<int, QColor >mColors;
    QList<QPoint> mSelection;
    int mSelectorSize;
    bool mShowGrid;

};

//==== GridWidget
#endif // GRIDWIDGET_H
