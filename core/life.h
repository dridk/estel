#ifndef LIFE_H
#define LIFE_H
#include "genom.h"
#include <QPoint>
#include "lifeengine.h"
class Life;
class LifeEngine;
class Life
{
public:
    enum Status {Replicate, Dead, Live};
    Life();
    void setPos(const QPoint& pos);
    void setPos(int x, int y);
    void setAge(int age);
    const QPoint& pos() const;
    Life muted() const;
    void mutate();

    int x() const;
    int y() const;
    int age() const;
    const Genom & genom() const;
    virtual void step(LifeEngine * engine);
    QList<Life*> childs() const;
    void makeOlder(int add=1);
    Status status();
    void setStatus(Status s);

    void clearChilds();




private:
    Genom mGenom;
    int mAge;
    QPoint mPos;
    QList<Life*> mChilds;
    Status mStatus;

    Gene mA;
    Gene mB;
};

#endif // LIFE_H
