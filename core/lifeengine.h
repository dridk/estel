#ifndef LIFEENGINE_H
#define LIFEENGINE_H
#include <QList>
#include "life.h"
#include "project.h"
class Life;
class LifeEngine;
class LifeEngine
{
public:
    LifeEngine(int rows, int columns);
    ~LifeEngine();
    void addLife(Life * life);
    void addLifes(QList<Life*> lifes);
    void remLife(int x, int y);
    QList<Life*> lifes() const;

    void clear();
    void run(int iteration = 100);
    void step();
    int population();
    void setFileName(const QString& file);
    const QString& filename() const;
    void load(const QString& filename);

    int rows() const;
    int columns() const;
    int currentStep() const;



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
