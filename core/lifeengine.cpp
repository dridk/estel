#include "lifeengine.h"
#include <QDebug>
LifeEngine::LifeEngine(int rows, int columns)
    :QObject()

{
    mRows = rows;
    mColumns = columns;
    mFilename =QString();
    mCurrentStep = 0;

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
    mCurrentStep = 0;
    mProject.setName("experimentA");
    mProject.setAuthor("sacha schutz");
    mProject.setSummary("beta testing simulation");

    while (mCurrentStep < iteration)
    {
        mProject.writeData(this);

        step();
        qDebug()<<mCurrentStep<<" pop"<<population();

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
    mCurrentStep++;

}

int LifeEngine::population()
{
    return mLifeList.count();
}

void LifeEngine::setFileName(const QString &file)
{
    mFilename = file;
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



const QString &LifeEngine::filename() const
{
    return mFilename;
}

void LifeEngine::load(const QString &filename)
{
    mLifeList.clear();
    mProject.readData(filename, this);

}

int LifeEngine::rows() const
{
    return mRows;
}

int LifeEngine::columns() const
{
    return mColumns;
}

int LifeEngine::currentStep() const
{
    return mCurrentStep;
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


