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

#include "lifefilterwidget.h"
#include <QPainter>
LifeFilterWidget::LifeFilterWidget(QWidget *parent) :
    QTreeView(parent)
{
    mEngineView = NULL;
    mModel = new QStandardItemModel;
    setModel(mModel);

    setWindowTitle("Life filter");


    QAction * refreshAction = new QAction("refresh",this);
    connect(refreshAction,SIGNAL(triggered()),this,SLOT(refresh()));
    connect(mModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(itemChanged(QStandardItem*)));
    addAction(refreshAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

}

void LifeFilterWidget::setEngineView(LifeEngineView *view)
{
    mEngineView = view;
    connect(mEngineView->engine(),SIGNAL(changed()),this,SLOT(refresh()));
}

void LifeFilterWidget::refresh()
{
    mModel->clear();
    QHash<QString,Life*> lifes;
    QStringList lifeFilter;
    QStringList geneFilter;
    foreach (Life * life,mEngineView->engine()->lifes())
        lifes.insert(life->name(),life);

    foreach (Life * life, lifes.values())
    {

        QStandardItem * rootItem  = new QStandardItem;
        rootItem->setText(life->name() + QString(" (%1)").arg(mEngineView->engine()->count()));
        rootItem->setData(life->name());
        rootItem->setCheckable(true);
        rootItem->setEditable(false);
        rootItem->setCheckState(Qt::Checked);
        lifeFilter.append(life->name());


        foreach (Gene gene, life->genom().genes())
        {
            QStandardItem * item  = new QStandardItem;


            item->setText(gene.name());
            item->setData(gene.name());
            item->setCheckable(true);
            item->setEditable(false);
            item->setCheckState(Qt::Checked);


            geneFilter.append(gene.name());
            QPixmap pix(16,16);
            pix.fill(Qt::transparent);
            QPainter paint(&pix);
            paint.setRenderHint(QPainter::Antialiasing,true);
            paint.setBrush(QBrush(gene.rootColor()));
            paint.setPen(Qt::NoPen);
            paint.drawEllipse(QRect(0,0,15,15));
            item->setIcon(QIcon(pix));

            rootItem->appendRow(item);
        }


        mModel->appendRow(rootItem);
    }


    mEngineView->engine()->setLifeFilter(lifeFilter);
    mEngineView->engine()->setGeneFilter(geneFilter);




}

void LifeFilterWidget::itemChanged(QStandardItem *item)
{

    if (mEngineView == NULL)
        return;

    for (int i=0; i<item->rowCount(); ++i)
        item->child(i)->setEnabled(item->checkState() == Qt::Checked);

    QStringList lifeFilter;
    QStringList geneFilter;

    for (int i=0; i<mModel->rowCount(); ++i)
    {

        if (mModel->item(i)->checkState() == Qt::Checked)
        {
            lifeFilter<<mModel->item(i)->data().toString();
            for (int j=0; j<mModel->item(i)->rowCount(); ++j) {
                if (mModel->item(i)->child(j)->checkState() == Qt::Checked)
                    geneFilter<<mModel->item(i)->child(j)->data().toString();

            }
        }
    }

    mEngineView->engine()->setLifeFilter(lifeFilter);
    mEngineView->engine()->setGeneFilter(geneFilter);
    mEngineView->refresh();
}
