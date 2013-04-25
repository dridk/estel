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

#include "lifeenginethread.h"
#include <QDebug>
LifeEngineThread::LifeEngineThread(QObject *parent) :
    QThread(parent)
{
    mEngine = NULL;

}

void LifeEngineThread::setEngine(LifeEngine *engine)
{
    mEngine = engine;
}

void LifeEngineThread::run()
{
    qDebug()<<"start "<<mEngine;
    emit runningChanged(true);
    if (mMode == StepMode)
        mEngine->step();

    if (mMode == LoadMode)
        mEngine->load(mFileName);

    if (mMode == SaveMode)
        mEngine->save(mFileName);

    emit runningChanged(false);
    qDebug()<<"finished";


}

void LifeEngineThread::save(const QString &filename)
{
    mFileName = filename;
    mMode = SaveMode;
    start();
}

void LifeEngineThread::load(const QString &filename)
{
    mFileName = filename;
    mMode = LoadMode;
    start();
}

void LifeEngineThread::step()
{
   mMode = StepMode;
   start();
}
