#ifndef LIFE_H
#define LIFE_H
#include "genom.h"
#include <QPoint>
#include <QObject>
#include "lifeengine.h"
class Life;
class LifeEngine;
class Life : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int age READ age WRITE setAge )
    Q_PROPERTY (int x READ x WRITE setX )
    Q_PROPERTY (int y READ y WRITE setY )

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

    Q_INVOKABLE Gene & gene(const QString& name);
    Q_INVOKABLE void replicate(int x, int y);

    const Genom & genom() const;
    const QString& name() const;
    const QString& script()const;

    int geneValue(const QString& name);
    LifeEngine * engine();

    void addGene(Gene  gene);
    void remGene(Gene  gene);

    void setGenom(const Genom& genom);
    void setName(const QString& name);
    void setEngine(LifeEngine * engine);
    void setScript(const QString& script);
    void loadScript(const QString& filename);

    virtual bool step();
    virtual void init();


    void debug();


private:
    Genom mGenom;
    int mAge;
    QPoint mPos;
    QString mName;
    QString mScript;

    LifeEngine * mEngine;


};

#endif // LIFE_H
