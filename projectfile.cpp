#include "projectfile.h"
#include "life.h"
#include "lifeengine.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
ProjectFile::ProjectFile(QObject *parent) :
    QObject(parent)
{




}

void ProjectFile::writeData(int time, LifeEngine *engine)
{


//    QVariantList lifeList;

//    foreach (Life * life, engine->lifes())
//    {
//        QVariantHash lMap;
//        lMap.insert("x",life->x());
//        lMap.insert("y",life->y());
//        lMap.insert("age",life->age());

//        QVariantList geneList;
//        foreach (Gene * gene, life->genom().genes())
//        {
//            QVariantHash gMap;
//            gMap.insert("name",gene->name());
//            gMap.insert("value",gene->value());
//            gMap.insert("proba",gene->mutationProbability());
//            gMap.insert("variance",gene->variance());
//            geneList.append(gMap);
//        }
//        lMap.insert("genom",geneList);
//        lifeList.append(lMap);
//    }

//    mSteps.insert("lifes",lifeList);
//    mSteps.insert("time",time);
//    mSteps.insert("population",engine->population());


//    qDebug()<<mSteps;
//    mFiles.write(mJson.stringify(mSteps).toUtf8());


//    mSteps.clear();

}

//void ProjectFile::open(const QString &filename)
//{

//    mFiles.setFileName("simulation.json");
//    if (!mFiles.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;




//}

//void ProjectFile::close()
//{


//    mFiles.close();

//}

