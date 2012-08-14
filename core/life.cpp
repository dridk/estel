#include "life.h"
#include <QFile>

Life::Life(int x, int y, int age)


{
    mAge = age;
    mPos = QPoint(x,y);
    mName = "Life";
    mEngine = NULL;


}


void Life::setPos(const QPoint &pos)
{
    mPos = pos;
}

void Life::setPos(int x, int y)
{
    mPos = QPoint(x,y);
}

void Life::setX(int x)
{
    mPos.setX(x);
}

void Life::setY(int y)
{
    mPos.setY(y);
}

void Life::setAge(int age)
{
    mAge = age;
}

const QPoint &Life::pos() const
{
    return mPos;
}

Life * Life::muted() const
{
    Life * newLife = new Life(x(),y(),0);
    newLife->setGenom(genom());
    newLife->mutate();
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

void Life::setGenom(const Genom &genom)
{
    mGenom = Genom(genom);
}




bool Life::step()
{

//    mAge++;

////    if ( mAge > 10)
////        return false;


//    if (mAge%2 && mAge != 1)
//    {



//        Life * child = new Life(muted());
//       child->setPos(x()+(qrand()%3)-1, y()+(qrand()%3)-1);
////       qDebug()<<child->pos();
//       engine()->addLife(child);


//    }

//    return true;

    return true;


}

void Life::init()
{
}

void Life::addGene(Gene gene)
{
    mGenom.add(gene);
}

void Life::remGene(Gene gene)
{
    mGenom.rem(gene);
}

Gene& Life::gene(const QString &name)
{
    return mGenom.gene(name);
}

void Life::debug()
{
    qDebug()<<x()<<"-"<<y()<<" age = "<<age();
}

void Life::setName(const QString &name)
{
    mName = name;
}

const QString &Life::name() const
{
    return mName;
}

void Life::setEngine(LifeEngine *engine)
{
    mEngine = engine;
}

LifeEngine *Life::engine()
{
    return mEngine;
}

void Life::setScript(const QString &script)
{
    mScript = script;
}

const QString &Life::script()
{
    return mScript;
}

void Life::loadScript(const QString &filename)
{
    QFile file(filename);
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           qDebug()<<"cannot load file "<<filename;
           return;
       }

      mScript = file.readAll();


      file.close();

}








