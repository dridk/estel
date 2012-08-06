#include "life.h"

Life::Life()
{
    mAge = 0;
    mPos = QPoint(0,0);

    mA = 4;
    mB = 6;

    mGenom.add(&mA);
    mGenom.add(&mB);

}


void Life::setPos(const QPoint &pos)
{
    mPos = pos;
}

void Life::setPos(int x, int y)
{
    mPos = QPoint(x,y);
}

void Life::setAge(int age)
{
    mAge = age;
}

const QPoint &Life::pos() const
{
    return mPos;
}

Life Life::muted() const
{
    Life newLife = *this;
    newLife.mutate();
    return newLife;
}

void Life::mutate()
{
    mGenom.mutate();
}

int Life::x() const
{
    return mPos.x();
}

int Life::y() const
{
    return mPos.y();
}

int Life::age() const
{
    return mAge;
}

const Genom &Life::genom() const
{
    return mGenom;
}




void Life::step(LifeEngine *engine)
{


    if (mAge > 10){
        qDebug()<<"kill";
        setStatus(Life::Dead);
        return;
    }

    if (mAge % 3 )
    {
        Life * newLife = new Life(*this);
        newLife->setPos(qrand()%engine->rows(), y()+1);
        newLife->setAge(0);
        mChilds.append(newLife);
        setStatus(Life::Replicate);
        return;
    }

    setStatus(Life::Live);
}

QList<Life*> Life::childs() const
{
    return mChilds;
}

void Life::makeOlder(int add)
{
    mAge+=add;
}

Life::Status Life::status()
{
    return mStatus;
}

void Life::setStatus(Life::Status s)
{
    mStatus = s;
}

void Life::clearChilds()
{
    mChilds.clear();
}








