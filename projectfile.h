#ifndef PROJECTFILE_H
#define PROJECTFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "qxtjson.h"

class Life;
class LifeEngine;
class ProjectFile : public QObject
{
    Q_OBJECT
public:
    explicit ProjectFile(QObject *parent = 0);
    void writeStep(int population, int time);
    void writeLife(Life * life);
    void writeData(int time, LifeEngine * engine );
    void open(const QString& filename);
    void close();
    

private:
    QVariantList mRoot;
    QVariantHash mSteps;
    QFile mFiles;
    QTextStream mOut;
    QxtJSON mJson;

    
};

#endif // PROJECTFILE_H
