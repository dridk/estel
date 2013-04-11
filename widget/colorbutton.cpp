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

#include "colorbutton.h"
#include <QPainter>
ColorButton::ColorButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(openColorDialog()));
}

void ColorButton::setColor(const QColor &col)
{
    mColor = col;
    QPixmap pix(32,32);
    pix.fill(Qt::transparent);
    QPainter paint(&pix);
    paint.setRenderHint(QPainter::Antialiasing,true);
    paint.setBrush(QBrush(col));
    paint.setPen(Qt::NoPen);
    paint.drawEllipse(QRect(0,0,31,31));

    setIcon(QIcon(pix));

    emit colorChanged(mColor);


}

const QColor &ColorButton::color() const
{
    return mColor;
}

void ColorButton::openColorDialog()
{
    QColor col = QColorDialog::getColor();
    setColor(col);

}
