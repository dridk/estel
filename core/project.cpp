#include "project.h"
#include "lifeengine.h"
#include <QDebug>
#include <QFile>
#include "qxtjson.h"

Project::Project(QObject *parent) :
    QObject(parent)
{


}

void Project::setName(const QString &name)
{
    mName = name;
}

void Project::setSummary(const QString &summary)
{
    mSummary = summary;
}

void Project::setAuthor(const QString &author)
{
    mAuthor = author;
}

void Project::writeData(LifeEngine *engine)
{

    QString filename = mName+"-"+QString::number(engine->currentStep())+".json";

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"cannot open file "<<filename;
        return;
    }


    QVariantHash root;
    QVariantList lifeList;
    QVariantHash information;


    information.insert("time", engine->currentStep());
    information.insert("population", engine->population());
    information.insert("name",mName);
    information.insert("author",mAuthor);
    information.insert("summary",mSummary);
    information.insert("date",QDateTime::currentDateTime().toString("hh:mm:ss dd-MM-yyyy"));




    foreach (Life * life, engine->lifes())
    {
        QVariantHash lMap;
        lMap.insert("x",life->x());
        lMap.insert("y",life->y());
        lMap.insert("age",life->age());

        QVariantList geneList;
        foreach (Gene  gene, life->genom().genes())
        {
            QVariantHash gMap;
            gMap.insert("name",gene.name());
            gMap.insert("value",gene.value());
            gMap.insert("proba",gene.mutationProbability());
            gMap.insert("variance",gene.variance());
            geneList.append(gMap);
        }
        lMap.insert("genom",geneList);
        lifeList.append(lMap);
    }

    root.insert("lifes",lifeList);
    root.insert("meta",information);



    file.write(QxtJSON::stringify(root).toUtf8());


    file.close();

}

void Project::readData(const QString &filename, LifeEngine *engine)
{

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"cannot open file "<<filename;
        return;
    }


    QVariant result = QxtJSON::parse(file.readAll());

    QVariantMap root = result.toMap();

    for (int i=0; i <root["lifes"].toList().count(); ++i)
    {

        QVariantMap lifeMap = root["lifes"].toList().at(i).toMap();
        int x = lifeMap["x"].toInt();
        int y = lifeMap["y"].toInt();
        int age = lifeMap["age"].toInt();

        Life * life = new Life(x,y,age);


        QVariantList genomList = lifeMap["genom"].toList();

        foreach (QVariant geneMap, genomList)
        {

            int value = geneMap.toMap().value("value").toInt();
            int min = geneMap.toMap().value("min").toInt();
            int max = geneMap.toMap().value("max").toInt();
            double proba = geneMap.toMap().value("proba").toDouble();
            int variance = geneMap.toMap().value("variance").toInt();
            QString name = geneMap.toMap().value("name").toString();

//            Gene * gene = new Gene(name);
//            gene->setValue(value);
//            gene->setLimit(min,max);
//            gene->setMutationProbability(proba);
//            gene->setName(name);
//            gene->setVariance(variance);

//            life->addGene(gene);


        }

        engine->addLife(life);

    }







}
