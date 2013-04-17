#include "life.h"
#include <QFile>
#include "qxtjson.h"
Life::Life(int x, int y, int age)
{
    mAge = age;
    mPos = QPoint(x,y);
    mName = "Life";
    mEngine = NULL;
}

Life::Life(const Life &life)
{
    clone(life);
}

void Life::clone(const Life &life)
{
    setAge(life.age());
    setPos(life.pos().x(),life.pos().y());
    setName(life.name());
    setEngine(life.engine());
    setGenom(life.genom());
    setScript(life.script());
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

Life Life::muted() const
{
    Life newLife = Life(x(),y(),0);
    newLife.setGenom(genom());
    newLife.setScript(script());
    newLife.setName(name());
    newLife.mutate();
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

int Life::index() const
{
    if (mEngine == NULL)
        return -1;
    return mEngine->columns()*x() + y();
}

const Genom &Life::genom() const
{
    return mGenom;
}

void Life::setGenom(const Genom &genom)
{
    mGenom.clear();
    foreach (Gene g, genom.genes())
        mGenom.append(g);


}




bool Life::step()
{
    mAge++;
    int i =  qrand()%7;
    qDebug()<<"val" <<i;
    int ax=0;
    int ay=0;
    switch ( i)
    {
    case 0 : ax=-1; ay=-1;break;
    case 1 : ax=0; ay=-1;break;
    case 2 : ax=1; ay=-1;break;
    case 3 : ax=-1; ay=0;break;
    case 4 : ax=1; ay=0;break;
    case 5 : ax=-1; ay=1;break;
    case 6 : ax=-0; ay=1;break;
    case 7 : ax=1; ay=1;break;

    }

    int d = qrand()%4 + 1;


    replicate(x() + ax * d, y() + ay * d);


    if ( mAge > 4)
        return false;

    return true;
}


void Life::init()
{
}

void Life::addGene(Gene gene)
{
    mGenom.append(gene);
}

void Life::remGene(Gene gene)
{
    mGenom.remove(gene);
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
    if (engine() == NULL)
        return;

    if (!engine()->hasLife(x,y))
    {
        Life * child = new Life(*this);
        child->setPos(x,y);
        child->mutate();
        engine()->addLife(child);
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

LifeEngine *Life::engine() const
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

    QString script = life->script();
    script = script.replace("\"", "&quot;");
    dataMap.insert("script", script);

    QVariantList geneList;
    foreach (Gene  gene,life->genom().genes())
    {
        QVariantHash gMap;
        gMap.insert("name",gene.name());
        gMap.insert("value",gene.value());
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
        gene.setVariance(geneData.toMap().value("variance").toInt());
        gene.setMutationProbability(geneData.toMap().value("proba").toDouble());
        gene.setRootColor(QColor(geneData.toMap().value("rootcolor").toString()));

        life->addGene(gene);
    }

    //=== load script
    QString array = data.toMap().value("script").toString();
    array = array.replace("&quot;", "\"");
    QString script = array;
    life->setScript(script);

}
const QString &Life::script() const
{
    return mScript;
}










