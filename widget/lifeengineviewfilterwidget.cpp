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

#include "lifeengineviewfilterwidget.h"

LifeEngineViewFilterWidget::LifeEngineViewFilterWidget(QWidget *parent):
    QTableView(parent)
{

    mEngineView = NULL;
    mModel = new QStandardItemModel;
    mDelegate = new LifeEngineViewFilterDelegate;
    mModel->setColumnCount(2);
    setItemDelegate(mDelegate);
    verticalHeader()->hide();
    verticalHeader()->setDefaultSectionSize(22);
    setShowGrid(false);
    setModel(mModel);
    setWindowTitle("Filter");


    QAction * refreshAction = new QAction("refresh",this);
    connect(refreshAction,SIGNAL(triggered()),this,SLOT(refresh()));
    addAction(refreshAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setDefaultSectionSize(10);

    connect(mModel,SIGNAL(itemChanged(QStandardItem*)),this,SIGNAL(changed()));



}

void LifeEngineViewFilterWidget::setEngineView(LifeEngineView *view)
{
    mEngineView = view;

}

QString LifeEngineViewFilterWidget::lifeName(int row) const
{
    if (mModel->hasIndex(0,0))
        return mModel->item(row)->text();
    else
        return QString();

}

QString LifeEngineViewFilterWidget::geneName(int row) const
{
    if (mModel->hasIndex(0,1))
        return mModel->item(row,1)->text();
    else
        return QString();
}

bool LifeEngineViewFilterWidget::checked(int row) const
{
    return mModel->item(row)->checkState() == Qt::Checked;
}

int LifeEngineViewFilterWidget::count() const
{
    return mModel->rowCount();
}

void LifeEngineViewFilterWidget::refresh()
{
    Q_ASSERT_X (mEngineView != NULL , "LifeEngineViewFilterWidget", "No engineview set ");

    qDebug()<<"refresh filter";
    mGenesFilter.clear();
    mModel->clear();
    mDelegate->clearLife();

    foreach (Life * life, mEngineView->engine()->lifes())
        mDelegate->addLife(life->name(),*life);


    foreach (Life life, mDelegate->lifes())
    {
        QStandardItem * item = new QStandardItem;
        item->setText(life.name());


        item->setCheckable(true);
        item->setCheckState(Qt::Checked);
        item->setEditable(false);

        QStandardItem * geneItem = new QStandardItem;

        if (life.genom().count() > 0)
        {
            geneItem->setText(life.genom().genes().first().name());
            geneItem->setEditable(true);
            geneItem->setEnabled(true);
        }
        else
        {
            geneItem->setText("no genes");
            geneItem->setEditable(false);
            QFont font = geneItem->font();
            font.setItalic(true);
            geneItem->setFont(font);
            geneItem->setData(Qt::lightGray,Qt::TextColorRole);
        }

        geneItem->setData(life.name());


        QList<QStandardItem*> list;
        list.append(item);
        list.append(geneItem);
        mModel->appendRow(list);

    }


}
