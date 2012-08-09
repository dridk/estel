#ifndef LIFEENGINE_H
#define LIFEENGINE_H
#include <QList>
#include <QObject>
#include "life.h"
#include "project.h"
class Life;
class LifeEngine;
class LifeEngine : public QObject
{
    Q_OBJECT
public:
    LifeEngine(int rows, int columns);
    ~LifeEngine();
    Q_INVOKABLE void addLife(Life * life);
    Q_INVOKABLE void addLifes(QList<Life*> lifes);
    Q_INVOKABLE void remLife(int x, int y);
    Q_INVOKABLE QList<Life*> lifes() const;
    Q_INVOKABLE void clear();
    Q_INVOKABLE int population();
    Q_INVOKABLE int rows() const;
    Q_INVOKABLE int columns() const;
    Q_INVOKABLE int currentStep() const;

    void setFileName(const QString& file);
    const QString& filename() const;
    void load(const QString& filename);
    void run(int iteration = 100);
    void step();



private:
    QHash<int,Life*> mLifeList;
    int mRows;
    int mColumns;
    QString mFilename;
    QVariant mDatas;
    Project mProject;
    int mCurrentStep;

};

#endif // LIFEENGINE_H
