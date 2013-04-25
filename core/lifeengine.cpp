#include "lifeengine.h"
#include <QDebug>
#include <QFile>
#include "qxtjson.h"
LifeEngine::LifeEngine(int rows, int columns)
    :QObject()

{
    mRows = rows;
    mColumns = columns;
    mScriptEngine = new LifeScriptEngine;
    mScriptEngine->setLifeEngine(this);



}

LifeEngine::~LifeEngine()
{
    mLifeList.clear();
}

bool LifeEngine::addLife(Life *life)
{

    int index =  mColumns * life->x()  + life->y();

    if (life->x() > mRows ||life->x()<0 || life->y() > mColumns || life->y()<0)
    {
        //qDebug()<<"life pos out of grid";
        return false;
    }

    if (mLifeList.keys().contains(index)) {
        //qDebug()<<"life already set for this position "<<life->pos();
        return false;
    }

    if (index >= mRows * mColumns){
        //qDebug()<<"life position out of range";
        return false;
    }

    mLifeList.insert(index,life);
    life->setEngine(this);
    life->init();
    return true;
}

bool LifeEngine::remLife(int x, int y)
{
    int index =  mColumns * x + y;
    if (mLifeList.keys().contains(index)){
        mLifeList.remove(index);
        return true;
    }
    return false;
}

bool LifeEngine::remLife(Life *life)
{

    if (mLifeList.values().contains(life))
    {
       mLifeList.remove(mLifeList.key(life));
       return true;
    }
    return false;
}

QList<Life*> LifeEngine::lifes()
{
    return mLifeList.values();
}

void LifeEngine::clear()
{
    mLifeList.clear();
    emit changed();
}
void LifeEngine::run(int iteration)
{
    int currentStep = 0;

    while (currentStep < iteration)
    {
        step();
        qDebug()<<currentStep<<" pop"<<population();
        currentStep++;

    }

    qDebug()<<"end of simulation";

}

void LifeEngine::step()
{
    QList<Life*> lifes = mLifeList.values();
    QList<Life*>::iterator it = lifes.begin();
    int total = lifes.count();
    int now   = 0;
    while (it != lifes.end()) {

        Life * currentLife = *it;
        bool isLive = mScriptEngine->evaluateLife(currentLife);
        if (!isLive){
            int index = currentLife->index();
            it = lifes.erase(it);
            mLifeList.remove(index);
        }
        else it++;
        emit progress(qRound(float(now)*100/float(total)), QString("computing life %1").arg(now));
        ++now;
    }
    emit progress(0);
    emit changed();

    //    while (it != mLifeList.end()) {

    //        Life * currentLife = it;
    ////        bool isLive = currentLife->step();

    ////        if (!isLive){
    ////            i = mLifeList.erase(i);
    ////        }
    ////        else i++;
    //    }

}



int LifeEngine::population()
{
    return mLifeList.count();
}


bool LifeEngine::load(const QString &filename)
{
    mLifeList.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    clear();
    QByteArray array = file.readAll();
    emit progress(1,"uncompressing");
    array = qUncompress(array);

    QVariant data = QxtJSON::parse(QString::fromUtf8(array));
    QVariantList lifeList = data.toMap().value("lifes").toList();

    int total = lifeList.count();
    int now   = 0;
    foreach (QVariant lifeData, lifeList)
    {
        Life * life = new Life;
        Life::parse(QxtJSON::stringify(lifeData),life);
        addLife(life);

        emit progress(qRound(float(now)*100/float(total)),"loading");
        ++now;
    }
    file.close();
    emit progress(0);
    return true;
}

bool LifeEngine::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QVariantList lifeList;
    int total = lifes().count();
    int now   = 0;
    foreach (Life * l, lifes()){
        lifeList.append(QxtJSON::parse(Life::serialize(l)));
        emit progress(qRound(float(now)*100/float(total)),"saving");
        ++now;
    }



    QVariantMap globalMap;
    globalMap.insert("date",QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm"));
    globalMap.insert("lifes", lifeList);

    QByteArray array = QxtJSON::stringify(globalMap).toUtf8();
    emit progress(100,"compressing");
    file.write(qCompress(array,9));
    file.close();
     emit progress(0);
    return true;
}

int LifeEngine::rows() const
{
    return mRows;
}

int LifeEngine::columns() const
{
    return mColumns;
}



bool LifeEngine::hasLife(int x, int y) const
{

    int index =  columns() * x + y;
    if (mLifeList.contains(index)){
        return true;
    }
    return false;

}

Life *LifeEngine::life(int x, int y)
{
    int index =  mColumns * x + y;
    if (mLifeList.contains(index))
        return mLifeList[index];
    else
        return NULL;
}

QObject *LifeEngine::lifeAt(int x, int y)
{
    Life * lf = life(x,y);
    if (lf)
        return new LifeObject(lf);
    else
        return NULL;
}

int LifeEngine::count() const
{
 return mLifeList.count();
}


