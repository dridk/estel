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

#include "lifeengineviewfilterdelegate.h"

LifeEngineViewFilterDelegate::LifeEngineViewFilterDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *LifeEngineViewFilterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   QString name = index.data(Qt::UserRole+1).toString();
   GeneComboBox * combo = new GeneComboBox(parent);

   qDebug()<<"name : "<<name;
   qDebug()<<"life is "<<mLifes[name].name();

   combo->setLife(mLifes[name]);
   return combo;
}

void LifeEngineViewFilterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    GeneComboBox *combo = qobject_cast<GeneComboBox*>(editor);



}

void LifeEngineViewFilterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    GeneComboBox *combo = qobject_cast<GeneComboBox*>(editor);
    model->setData(index, combo->currentGene().name());

    QPixmap pix(16,16);
    pix.fill(combo->currentGene().rootColor());



}

void LifeEngineViewFilterDelegate::addLife(const QString &name, const Life &life)
{
    mLifes[name] = Life(life);
}

void LifeEngineViewFilterDelegate::clearLife()
{
    mLifes.clear();
}
