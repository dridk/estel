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

    //    mAge++;

    ////    if ( mAge > 10)
    ////        return false;


    //    if (mAge%2 && mAge != 1)
    //    {



    //        Life * child = new Life(muted());
    //       child->setPos(x()+(qrand()%3)-1, y()+(qrand()%3)-1);
    ////       qDebug()<<child->pos();
    //       engine()->addLife(child);


    //    }

    //    return true;

    return true;


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

int Life::g(const QString &name)
{
    return mGenom.gene(name).value();
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

bool Life::loadFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"error"<<file.errorString();
        return false;
    }

    Life * tmpLife = Life::parse(file.readAll());

    setName(tmpLife->name());
    setAge(tmpLife->age());
    setPos(tmpLife->pos());
    setGenom(tmpLife->genom());
    setScript(tmpLife->script());

    delete tmpLife;

    file.close();

    return true;
}

bool Life::saveFile(const QString &filename)
{
    //========= save script ============
    QFileInfo fileInfo(filename);
    setName(fileInfo.baseName());
    QFile scriptFile(name()+"_script.js");
    if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    scriptFile.write(script().toUtf8());
    scriptFile.close();

    //========== save life =============
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QString data = Life::serialize(this);
    file.write(data.toUtf8());
    file.close();

    return true;

}

QString Life::serialize(Life *life)
{
    QVariantMap dataMap;
    dataMap.insert("name", life->name());
    dataMap.insert("x", life->x());
    dataMap.insert("y", life->y());
    dataMap.insert("age", life->age());
    dataMap.insert("script", life->name()+"_script.js");

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

    QString result = QxtJSON::stringify(dataMap);

    return result;

}

Life * Life::parse(const QString &json)
{
    Life * newLife = new Life;
    QVariant data = QxtJSON::parse(json);

    newLife->setName(data.toMap().value("name").toString());
    newLife->setAge(data.toMap().value("age").toInt());
    newLife->setX(data.toMap().value("x").toInt());
    newLife->setY(data.toMap().value("y").toInt());

    QVariantList genomData = data.toMap().value("genom").toList();

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

        newLife->addGene(gene);
    }

    //=== load script
    QString scriptFileName = data.toMap().value("script").toString();
    QFile scriptFile(scriptFileName);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return newLife;

    newLife->setScript(scriptFile.readAll());

    scriptFile.close();

    return newLife;
}

Life *Life::fromFile(const QString &filename)
{
    Life * life = new Life;
    if (!life->loadFile(filename))
    {
        qDebug()<<"cannot load files...";
        delete life;
        return NULL;
    }
    return life;
}

const QString &Life::script() const
{
    return mScript;
}










