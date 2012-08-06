#ifndef JSONFILE_H
#define JSONFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
class JsonFile;
class LifeEngine;
class JsonFile : public QObject
{
    Q_OBJECT
public:
     JsonFile(QObject *parent = 0);
    void open(const QString& filename);
    void close();
    void addStep(int step, int totalStep, LifeEngine * engine );

    
private:
    QFile mFile;
    QTextStream mOut;
    
};

#endif // JSONFILE_H
