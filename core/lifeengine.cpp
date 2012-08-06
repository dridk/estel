#include "lifeengine.h"
#include <QDebug>
LifeEngine::LifeEngine(int rows, int columns)
{
    mRows = rows;
    mColumns = columns;
}

void LifeEngine::addLife(Life *life)
{

    int index =  mColumns * life->x()  + life->y();

    if (mLifeList.keys().contains(index))
    {
        qDebug()<<"life already set for this position "<<life->pos();
        return;
    }

    if (index >= mRows * mColumns){
        qDebug()<<"life position out of range";
        return;
    }

    mLifeList.insert(index,life);
}

void LifeEngine::addLifes(QList<Life*> lifes)
{
    foreach (Life* l, lifes)
        addLife(l);
}

void LifeEngine::remLife(int x, int y)
{
    int index =  mColumns * x + y;
    if (mLifeList.keys().contains(index))
        mLifeList.remove(index);
}

QList<Life*> LifeEngine::lifes() const
{
    return mLifeList.values();
}


void LifeEngine::clear()
{
}

void LifeEngine::run(int iteration)
{
    int index = 0;

    mProject.open("simulation.json");

    while (index < iteration)
    {
        step();
        mProject.writeData(index,this);
        index++;
    }

    mProject.close();



}

void LifeEngine::step()
{
    QHash<int,Life*> ::iterator i = mLifeList.begin();

    //FIRST LOOP
    while (i != mLifeList.end()) {

        Life * currentLife = mLifeList[i.key()];
        currentLife->clearChilds();
         currentLife->step(this);
         currentLife->makeOlder();



         Life::Status status =  currentLife->status();
        if (status == Life::Dead){
            delete currentLife;
            i = mLifeList.erase(i);
        }
        else i++;
    }

    //SECOND LOOP
    for (int j=0, c=mLifeList.values().count(); j<c; ++j)
    {
        if (mLifeList.values()[j]->status() == Life::Replicate)
            addLifes(mLifeList.values()[j]->childs());

    }

    qDebug()<<"================";

}

int LifeEngine::count()
{
    return mLifeList.count();
}

void LifeEngine::setFileName(const QString &file)
{
    mFilename = file;
}

const QString &LifeEngine::filename() const
{
    return mFilename;
}

void LifeEngine::load(const QString &filename)
{
    mLifeList.clear();

}

int LifeEngine::rows() const
{
    return mRows;
}

int LifeEngine::columns() const
{
    return mColumns;
}


