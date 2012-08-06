#ifndef LIFEENGINE_H
#define LIFEENGINE_H
#include <QList>
#include "life.h"
#include "projectfile.h"
class Life;
class LifeEngine;
class LifeEngine
{
public:
    LifeEngine(int rows, int columns);
    void addLife(Life * life);
    void addLifes(QList<Life*> lifes);
    void remLife(int x, int y);
    QList<Life*> lifes() const;

    void clear();
    void run(int iteration = 100);
    void step();
    int count();
    void setFileName(const QString& file);
    const QString& filename() const;
    void load(const QString& filename);

    int rows() const;
    int columns() const;






private:
    QHash<int,Life*> mLifeList;
    int mRows;
    int mColumns;
    QString mFilename;
    QVariant mDatas;
    ProjectFile mProject;

};

#endif // LIFEENGINE_H
