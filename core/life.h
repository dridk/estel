#ifndef LIFE_H
#define LIFE_H
#include "genom.h"
#include <QPoint>
#include <QObject>
#include "lifeengine.h"
class Life;
class LifeEngine;
class Life
{
public:
    Life(int x=0, int y=0 , int age = 0);
    void setPos(const QPoint& pos);
    void setPos(int x, int y);
    void setX(int x);
    void setY(int y);
    void setAge(int age);
    const QPoint& pos() const;
    Life * muted() const;
    void mutate();

    int x() const;
    int y() const;
    int age() const;
    const Genom & genom() const;
    void setGenom(const Genom& genom);
    virtual bool step();
    virtual void init();
    void addGene(Gene  gene);
    void remGene(Gene  gene);
    Gene & gene(const QString& name);
    void debug();
    void setName(const QString& name);
    const QString& name() const;
    void setEngine(LifeEngine * engine);
    LifeEngine * engine();








private:
    Genom mGenom;
    int mAge;
    QPoint mPos;
    QString mName;
    LifeEngine * mEngine;


};

#endif // LIFE_H
