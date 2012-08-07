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
    mCurrentStep = 0;


    mProject.setName("experimentA");
    mProject.setAuthor("sacha schutz");
    mProject.setSummary("beta testing simulation");

    while (mCurrentStep < iteration)
    {
        qDebug()<<population();
        mProject.writeData(this);

        step();

        mCurrentStep++;
    }



}

void LifeEngine::step()
{
    QHash<int,Life*> ::iterator i = mLifeList.begin();
    while (i != mLifeList.end()) {

        Life * currentLife = mLifeList[i.key()];
        bool isLive = currentLife->step(this);

        if (!isLive){
            i = mLifeList.erase(i);
            delete currentLife;

        }
        else i++;
    }
}

int LifeEngine::population()
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
    mProject.readData(filename, this);

}

int LifeEngine::rows() const
{
    return mRows;
}

int LifeEngine::columns() const
{
    return mColumns;
}

int LifeEngine::currentStep() const
{
    return mCurrentStep;
}


