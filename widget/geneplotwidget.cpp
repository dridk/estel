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

#include "geneplotwidget.h"
#include <QAction>
GenePlotWidget::GenePlotWidget(QWidget *parent) :
    QCustomPlot(parent)
{
    mEngine = NULL;

    QAction * refreshAction = new QAction("refresh",this);
    connect(refreshAction,SIGNAL(triggered()),this,SLOT(refresh()));

    addAction(refreshAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);


}

void GenePlotWidget::setEngine(LifeEngine *engine)
{
    mEngine = engine;
}

void GenePlotWidget::refresh()
{
    if (mEngine == NULL)
        return;

    QHash<QString, QHash<QString, double > > datas;
    QHash<QString,Gene> genes;
    foreach (Life * life, mEngine->lifes())
    {

        foreach (Gene gene, life->genom().genes())
        {
            QString key = QString::number(gene.value());
            datas[gene.name()][key] = datas[gene.name()].value(key,0) + 1;

            genes[gene.name()] = gene;
        }
    }


    int index = 0;
    foreach (QString name, datas.keys())
    {

        addGraph();
        graph(index)->setName(name);


        QVector<double> keys;
        QVector<double> values;

        foreach (QString key, datas.value(name).keys())
        {
            keys.append(key.toDouble());
            values.append(datas.value(name).value(key));
        }



        graph(index)->setData(keys,values);
        graph(index)->setPen(QPen(genes[name].rootColor()));
        ++index;

    }


    rescaleAxes();
    replot();







}
