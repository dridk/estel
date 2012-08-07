#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QVariant>
#include <QDateTime>
class LifeEngine;
class Project : public QObject
{
    Q_OBJECT
public:
    explicit Project(QObject *parent = 0);
    void setName(const QString& name);
    void setSummary(const QString& summary);
    void setAuthor(const QString& author);
    void writeData(LifeEngine * engine);
    void readData(const QString& filename, LifeEngine * engine);
    

private:
QString mName;
QString mSummary;
QString mAuthor;
    
};

#endif // PROJECT_H
