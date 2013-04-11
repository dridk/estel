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

#include "genecombobox.h"
#include <QPainter>
GeneComboBox::GeneComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void GeneComboBox::setLife(const Life &life)
{
    mLife = life;
    clear();

    foreach (Gene gene, life.genom().genes())
    {
        QPixmap pix(16,16);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setBrush(QBrush(gene.rootColor()));
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(QRect(0,0,15,15));

        addItem(QIcon(pix), gene.name());



    }




}

Gene GeneComboBox::currentGene() const
{

    return mLife.genom().genes().at(currentIndex());



}
