#include "life.h"
#include <QFile>
#include "qxtjson.h"
Life::Life(int x, int y, int age)
    :QObject()
{
    mAge = age;
    mPos = QPoint(x,y);
    mName = "Life";
    mEngine = NULL;
}


void Life::setPos(const QPoint &pos)
{
    mPos = pos;
}

void Life::setPos(int x, int y)
{
    mPos = QPoint(x,y);
}

void Life::setX(int x)
{
    mPos.setX(x);
}

void Life::setY(int y)
{
    mPos.setY(y);
}

void Life::setAge(int age)
{
    mAge = age;
}

const QPoint &Life::pos() const
{
    return mPos;
}

Life * Life::muted() const
{
    Life * newLife = new Life(x(),y(),0);
    newLife->setGenom(genom());
    newLife->setScript(script());
    newLife->setName(name());
    newLife->mutate();
    return newLife;
}

void Life::mutate()
{
    mGenom.mutate();

}

int Life::x() const
{
    return mPos.x();
}

int Life::y() const
{
    return mPos.y();
}

int Life::age() const
{
    return mAge;
}

const Genom &Life::genom() const
{
    return mGenom;
}

void Life::setGenom(const Genom &genom)
{
    mGenom.clear();
    foreach (Gene g, genom.genes())
        mGenom.add(g);


}




bool Life::step()
{

}

void Life::init()
{
}

void Life::addGene(Gene gene)
{
    mGenom.add(gene);
}

void Life::remGene(Gene gene)
{
    mGenom.rem(gene);
}

void Life::clearGene()
{
    mGenom.clear();
}

Gene& Life::gene(const QString &name)
{
    return mGenom.gene(name);
}



void Life::replicate(int x, int y)
{
    if (!engine()->hasLife(x,y))
    {
        Life * child = muted();
        child->setPos(x,y);
        child->setAge(0);
        engine()->addLife(child);
        child->genom().debug();

    }

}


void Life::debug()
{
    qDebug()<<x()<<"-"<<y()<<" age = "<<age();
}

void Life::setName(const QString &name)
{
    mName = name;
}

const QString &Life::name() const
{
    return mName;
}

void Life::setEngine(LifeEngine *engine)
{
    mEngine = engine;
}

LifeEngine *Life::engine()
{
    return mEngine;
}

void Life::setScript(const QString &script)
{
    mScript = script;
}

QString Life::serialize(Life *life)
{
    QVariantMap dataMap;
    dataMap.insert("name", life->name());
    dataMap.insert("x", life->x());
    dataMap.insert("y", life->y());
    dataMap.insert("age", life->age());
    dataMap.insert("script", life->script());

    QVariantList geneList;
    foreach (Gene  gene,life->genom().genes())
    {
        QVariantHash gMap;
        gMap.insert("name",gene.name());
        gMap.insert("value",gene.value());
        gMap.insert("min",gene.min());
        gMap.insert("max",gene.max());
        gMap.insert("proba",gene.mutationProbability());
        gMap.insert("variance",gene.variance());
        gMap.insert("rootcolor",gene.rootColor().name());

        geneList.append(gMap);
    }

    dataMap.insert("genom", geneList);
    return QxtJSON::stringify(dataMap);

}

void Life::parse(const QString &json, Life *life)
{
    QVariant data = QxtJSON::parse(json);

    life->setName(data.toMap().value("name").toString());
    life->setAge(data.toMap().value("age").toInt());
    life->setX(data.toMap().value("x").toInt());
    life->setY(data.toMap().value("y").toInt());

    QVariantList genomData = data.toMap().value("genom").toList();

    life->clearGene();
    foreach (QVariant geneData, genomData)
    {
        Gene gene;
        gene.setName(geneData.toMap().value("name").toString());
        gene.setValue(geneData.toMap().value("value").toInt());
        gene.setLimit(geneData.toMap().value("min").toInt(),
                      geneData.toMap().value("max").toInt());
        gene.setVariance(geneData.toMap().value("variance").toInt());
        gene.setMutationProbability(geneData.toMap().value("proba").toDouble());
        gene.setRootColor(QColor(geneData.toMap().value("rootcolor").toString()));

        life->addGene(gene);
    }

    //=== load script
    QString script = data.toMap().value("script").toString();
    life->setScript(script);

}
const QString &Life::script() const
{
    return mScript;
}










