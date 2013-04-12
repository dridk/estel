#ifndef LIFE_H
#define LIFE_H
#include "genom.h"
#include <QPoint>
#include <QObject>
#include "lifeengine.h"
//! \class Life
//! \brief This class contain the Life information
//! It contains a Genom, XY coordination, an age and a logic script
//! Life can be serialized in Json Data.

class Life;
class LifeEngine;
class Life
{
public:
    Life(int x=0, int y=0 , int age = 0);
    Life(const Life& life);

    //! \brief Set the current life position
    void setPos(const QPoint& pos);

    //! \brief Set the current life position
    void setPos(int x, int y);

    //! \brief Set the X position
    void setX(int x);

    //! \brief Set the Y position
    void setY(int y);

    //! \brief Set the current age of life
    void setAge(int age);

    //! \return the current life position
    const QPoint& pos() const;

    //! \return a new muted life
    Life muted() const;

    //! \brief Mute the current life
    void mutate();

    //! \return x position of the current life
    int x() const;

     //! \return  y position of the current life
    int y() const;

     //! \return current age
    int age() const;

    int index() const;

     //! \return the gene from his name
     //! \param name : the name of gene
    Gene & gene(const QString& name);



    //! \brief replicate the current life at position
    //! \param x : x position
    //! \param y : y position
     void replicate(int x, int y);

    //! \return a reference of the life's genom.
    const Genom & genom() const;

    //! \return the life's name
    const QString& name() const;

    //! \return the life's logic script
    const QString& script()const;

    //! \return the LifeEngine where Life has been added
    LifeEngine * engine() const;

    //! \brief add a new gene
    void addGene(Gene gene);

    //! \brief rem gene. (note: it looks the gene name)
    void remGene(Gene gene);

    //! \brief remove all genes
    void clearGene();

    //! \brief add a genom for the current life
    void setGenom(const Genom& genom);

    //! \brief set life's name
    void setName(const QString& name);

    //! \brief set the engine. This method should'not be use.
    //! It's automatically called when Life is added.
    void setEngine(LifeEngine * engine);

    //! \brief set a logic script for the current life
    void setScript(const QString& script);

    //! \brief Serialize the life to Json data
    //! \return Json data
    static  QString serialize(Life * life);

    //! \brief Parse Json data and create a new Life
    //! \return new Life
    static  void parse(const QString& json, Life * life);

    //! \brief Compute Step.
    //! \brief Parse Json data and create a new Life
    //! \deprecated Logic script is used instead.  Use this function
    //! only if you want create a custom C++ Life
    virtual bool step();

    //! \brief Init before simulated
    //! this function is called once time before the LifeEngine start the simulation
    virtual void init();

    void debug();

    Gene& operator[](QString name) { return mGenom[name];}


private:
    Genom mGenom;
    int mAge;
    QPoint mPos;
    QString mName;
    QString mScript;
    LifeEngine * mEngine;


};

#endif // LIFE_H
