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

#ifndef LIFESCRIPTENGINE_H
#define LIFESCRIPTENGINE_H
#include <QScriptEngine>
#include "lifeengine.h"
class LifeScriptEngine;
class LifeEngine;
class Life;
class LifeObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString name READ name WRITE setName)
    Q_PROPERTY (int age READ age WRITE setAge)
    Q_PROPERTY (int x READ x WRITE setX)
    Q_PROPERTY (int y READ y WRITE setY)
    Q_PROPERTY (QVariantMap genom READ genom)
    Q_CLASSINFO("DefaultProperty", "genom")





public:
    LifeObject(Life * life, QObject * parent =0);

    const QString& name() const;
    void setName(const QString& name);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int age();
    void setAge(int a);

    QVariantMap genom();

public slots:
    Q_INVOKABLE void replicate(int x, int y);



private:
    Life * mLife;
};



class LifeScriptEngine : public QScriptEngine
{
    Q_OBJECT
public:
    explicit LifeScriptEngine(QObject *parent = 0);
    void setLifeEngine(LifeEngine * lifeEngine);
    bool evaluateLife(Life * life);
    Q_INVOKABLE void debug(const QString& message);


    const QString& lastError() const;
    const QString& lastDebug() const;

private:
    LifeEngine * mLifeEngine;
    QString mLastError;
    QString mLastDebug;

};

#endif // LIFESCRIPTENGINE_H
