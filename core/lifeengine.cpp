#include "lifeengine.h"
#include <QDebug>
#include <QFile>
#include "qxtjson.h"
LifeEngine::LifeEngine(int rows, int columns)
    :QObject()

{
    mRows = rows;
    mColumns = columns;

    QScriptValue object = mScriptEngine.newQObject(this);
    mScriptEngine.globalObject().setProperty("engine",object);

}

LifeEngine::~LifeEngine()
{
    mLifeList.clear();
}

void LifeEngine::addLife(Life *life)
{

    int index =  mColumns * life->x()  + life->y();

    if (mLifeList.keys().contains(index))
    {
        //        qDebug()<<"life already set for this position "<<life->pos();
        return;
    }

    if (index >= mRows * mColumns){
        //        qDebug()<<"life position out of range";
        return;
    }

    mLifeList.insert(index,life);
    life->setEngine(this);
    life->init();
}

void LifeEngine::addLifes(QList<Life*> lifes)
{
    foreach (Life* l, lifes)
        addLife(l);
}

void LifeEngine::remLife(int x, int y)
{
    int index =  mColumns * x + y;
    if (mLifeList.keys().contains(index))
        mLifeList.remove(index);
}


QList<Life*> LifeEngine::lifes() const
{
    return mLifeList.values();
}

void LifeEngine::clear()
{
    mLifeList.clear();
}
void LifeEngine::run(int iteration)
{
   int currentStep = 0;

    while (currentStep < iteration)
    {
        step();
        qDebug()<<currentStep<<" pop"<<population();
        currentStep++;

    }

    qDebug()<<"end of simulation";

}

void LifeEngine::step()
{
    QHash<int,Life*> ::iterator i = mLifeList.begin();
    while (i != mLifeList.end()) {

        Life * currentLife = mLifeList[i.key()];
        bool isLive = evaluateLife(currentLife);

        if (!isLive){
            i = mLifeList.erase(i);
        }
        else i++;
    }

}

int LifeEngine::population()
{
    return mLifeList.count();
}



bool LifeEngine::evaluateLife(Life *life)
{
    mLastError.clear();
    mLastDebug.clear();

    // Set context Property ....
    QScriptValue lifeObj = mScriptEngine.newQObject(life);
    mScriptEngine.globalObject().setProperty("life",lifeObj);

    //evaluate script

    QScriptValue result = mScriptEngine.evaluate(life->script());
    if (result.isError())
    {
        error("Error in script("
              +result.property("lineNumber").toString()+"):"
              +result.property("message").toString());
        qDebug()<<"script error";
        return true;
    }
    //evaluate function
    QScriptValue runFunction = mScriptEngine.globalObject().property("step");
    if (!runFunction.isFunction())
    {
        qDebug()<<"cannot find step function";
        error("cannot find step function");
    }


    qDebug()<<lastError();
    return runFunction.call().toBool();
}





bool LifeEngine::load(const QString &filename)
{
    mLifeList.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    clear();

    QVariant data = QxtJSON::parse(file.readAll());

    QVariantList lifeList = data.toMap().value("lifes").toList();

    foreach (QVariant lifeData, lifeList)
    {

        Life * life = Life::parse(QxtJSON::stringify(lifeData));
        addLife(life);

    }

    file.close();
    return true;



}

bool LifeEngine::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QVariantList lifeList;
    foreach (Life * l, lifes()){
        QVariantMap dataMap;
        dataMap.insert("name", l->name());
        dataMap.insert("x", l->x());
        dataMap.insert("y", l->y());
        dataMap.insert("age", l->age());
        dataMap.insert("script", l->name()+"_script.js");

        QVariantList geneList;
        foreach (Gene  gene,l->genom().genes())
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
        lifeList.append(dataMap);

    }

    QVariantMap globalMap;
    globalMap.insert("date",QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm"));
    globalMap.insert("lifes", lifeList);

    file.write(QxtJSON::stringify(globalMap).toUtf8());

    file.close();

    return true;



}

int LifeEngine::rows() const
{
    return mRows;
}

int LifeEngine::columns() const
{
    return mColumns;
}



bool LifeEngine::hasLife(int x, int y) const
{
    int index =  mColumns * x + y;
    if (mLifeList.contains(index))
        return true;
    return false;

}

void LifeEngine::debug(const QString &msg)
{
    mLastDebug.append(msg);
}

void LifeEngine::error(const QString &msg)
{
    mLastError.append(msg);
}

const QString &LifeEngine::lastDebug() const
{
    return mLastDebug;
}

const QString &LifeEngine::lastError() const
{
    return mLastError;
}


