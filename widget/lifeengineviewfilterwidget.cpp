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
   verticalHeader()->setMinimumSectionSize(10);
    setModel(mModel);
    setWindowTitle("Filter");


    QAction * refreshAction = new QAction("refresh",this);
    connect(refreshAction,SIGNAL(triggered()),this,SLOT(refresh()));
    addAction(refreshAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    horizontalHeader()->setDefaultSectionSize(10);



}

void LifeEngineViewFilterWidget::setEngineView(LifeEngineView *view)
{
    mEngineView = view;


}

void LifeEngineViewFilterWidget::refresh()
{
    Q_ASSERT_X (mEngineView != NULL , "LifeEngineViewFilterWidget", "No engineview set ");

    qDebug()<<"refresh filter";
    mGenesFilter.clear();
    mModel->clear();
    mDelegate->clearLife();

    foreach (Life * life, mEngineView->engine()->lifes()){
        mGenesFilter[life->name()] ="";
        mDelegate->addLife(life->name(),*life);

    }

    foreach (QString name, mGenesFilter.keys())
    {
        QStandardItem * item = new QStandardItem;
        item->setText(name);
        item->setCheckable(true);
        item->setCheckState(Qt::Checked);
        item->setEditable(false);

        QStandardItem * geneItem = new QStandardItem;
        geneItem->setText("gene");
        geneItem->setEditable(true);
        geneItem->setData(name);

        QList<QStandardItem*> list;
        list.append(item);
        list.append(geneItem);

        mModel->appendRow(list);

    }


}
