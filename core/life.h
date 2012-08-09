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
    Life(int x, int y , int age = 0);
    void setPos(const QPoint& pos);
    void setPos(int x, int y);
    void setX(int x);
    void setY(int y);
    void setAge(int age);
    const QPoint& pos() const;
    Life muted() const;
    void mutate();

    int x() const;
    int y() const;
    int age() const;
    const Genom & genom() const;
    virtual bool step(LifeEngine * engine);
    void addGene(Gene  gene);
    void remGene(Gene  gene);
    Gene & gene(const QString& name);
    void debug();






private:
    Genom mGenom;
    int mAge;
    QPoint mPos;
    QString mStepScript;


};

#endif // LIFE_H
