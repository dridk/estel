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

#include "lifescriptengine.h"

//======== LIFE object to be accessible for script engine =======
LifeObject::LifeObject(Life *life, QObject *parent)
{
    mLife = life;
}

const QString &LifeObject::name() const
{
    return mLife->name();
}

void LifeObject::setName(const QString &name)
{
    mLife->setName(name);
}

int LifeObject::x() const
{
    return mLife->x();
}

void LifeObject::setX(int x)
{
    mLife->setX(x);
}

int LifeObject::y() const
{
    return mLife->y();
}

void LifeObject::setY(int y)
{
    mLife->setY(y);
}

int LifeObject::age()
{
    return mLife->age();
}

void LifeObject::setAge(int a)
{
    mLife->setAge(a);
}

QVariantMap LifeObject::genom()
{
    QVariantMap list;
    foreach (Gene gene, mLife->genom().genes())
      list.insert(gene.name(),gene.value());

    return list;

}

void LifeObject::replicate(int x, int y)
{
    mLife->replicate(x,y);
}
//========= LIFE engine ========================================
LifeScriptEngine::LifeScriptEngine(QObject *parent) :
    QScriptEngine(parent)
{
    mLifeEngine = NULL;
}

void LifeScriptEngine::setLifeEngine(LifeEngine *lifeEngine)
{
    mLifeEngine = lifeEngine;
}

bool LifeScriptEngine::evaluateLife(Life *life)
{

    globalObject().setProperty("engine", newQObject(life->engine()));
    globalObject().setProperty("console",newQObject(this));
    globalObject().setProperty("life",newQObject(new LifeObject(life)));

    mLastError.clear();
    mLastDebug.clear();

    qDebug()<<"evaluate life ";

    QScriptValue result = evaluate(life->script());

    if (result.isError())
    {

        mLastError = QString("line %1 : %2 ")
                .arg(result.property("lineNumber").toString())
                .arg(result.property("message").toString());
        return false; // and kill the life
    }

    QScriptValue runFunction = globalObject().property("main");
    if (!runFunction.isFunction())
    {
        mLastError = QString("cannot find main() function");
        return false;
    }

    return runFunction.call().toBool();
    return true;
}

void LifeScriptEngine::debug(const QString &message)
{
    mLastDebug.append(message+"\n");
}

const QString &LifeScriptEngine::lastError() const
{
    return mLastError;
}

const QString &LifeScriptEngine::lastDebug() const
{
    return mLastDebug;
}


