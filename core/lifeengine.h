#ifndef LIFEENGINE_H
#define LIFEENGINE_H
#include <QList>
#include <QObject>
#include <QtScript>
#include "life.h"
//! \class LifeEngine
//! \brief LifeEngine contains all life in a grid and can make a simulation
//! by executing logic script of each life.
//! LifeEngine can be serialized in Json file

class Life;
class LifeEngine;
class LifeEngine : public QObject
{
    Q_OBJECT
public:
    //! \brief Constructor
    //! \param rows : the number of rows
    //! \param columns : the number of rows
    LifeEngine(int rows =100 , int columns=100);
    ~LifeEngine();

    //! \brief add life
    //! \param life : life pointer
    Q_INVOKABLE void addLife(Life * life);

    //! \brief rem life
    //! \param x : x position of the life to remove
    //! \param y : y position of the life to remove
    Q_INVOKABLE void remLife(int x, int y);

    //! \brief rem life
    //! \param Life* : Life pointer
    Q_INVOKABLE void remLife(Life * life);

    //! \return return all lifes
    Q_INVOKABLE QList<Life*> lifes() const;

    //! \brief clear all lifes
    Q_INVOKABLE void clear();

    //! \return lifes count
    Q_INVOKABLE int population();

    //! \return grid row count
    Q_INVOKABLE int rows() const;

    //! \return grid column count
    Q_INVOKABLE int columns() const;

    //! \brief check if a life exists at coord
    //! \param x : x position
    //! \param y : y position
    //! \return true if life exist, otherwise return false
    Q_INVOKABLE bool hasLife(int x, int y) const;

    //! \brief return life at position x,y. Use hasLife before using this function
    //! \param x : x position
    //! \param y : y position
    //! \return Life* if life exist, otherwise return NULL
    Q_INVOKABLE Life* life(int x, int y) const;

    //! \brief evaluate the logic script of life
    //! \return true if success, otherwise return false
    bool evaluateLife(Life * life);

    //! \brief load a simulation from a json file
    //! \return true is success, otherwise return false
    bool load(const QString& filename);

    //! \brief save a simulation to a json file
    //! \return true is success, otherwise return false
    bool save(const QString& filename);

    //! \brief Run simutation
    //! \deprecated Run function is made in GUI
    void run(int iteration = 100);

    //! \brief execute step on each Life.
    //! if Life::step() return false, remove it. Otherwise do nothing.
    void step();

    Q_INVOKABLE void debug(const QString& msg);
    Q_INVOKABLE void error(const QString& msg);

    const QString& lastDebug() const;
    const QString& lastError() const;

private:
    QHash<int,Life*> mLifeList;
    int mRows;
    int mColumns;
    QVariant mDatas;
    QScriptEngine mScriptEngine;
    QString mLastError;
    QString mLastDebug;

};

#endif // LIFEENGINE_H
