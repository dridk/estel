#include "lifeengine.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QPixmap>
#include <QPainter>
#include "qxtjson.h"
LifeEngine::LifeEngine(int rows, int columns)
    :QObject()

{
    mRows = rows;
    mColumns = columns;
    mScriptEngine = new LifeScriptEngine;
    mScriptEngine->setLifeEngine(this);



}

LifeEngine::~LifeEngine()
{
    mLifeList.clear();
}

bool LifeEngine::addLife(Life *life)
{
    if (life->x() > mRows ||life->x()<0 || life->y() > mColumns || life->y()<0)
    {
        //qDebug()<<"life pos out of grid";
        return false;
    }

    if (hasLife(life->x(), life->y())) {
        //qDebug()<<"life already set for this position "<<life->pos();
        return false;
    }


    mLifeList.append(life);
    life->setEngine(this);
    life->init();
    return true;
}

bool LifeEngine::remLife(int x, int y)
{
    int index =  mColumns * x + y;
    if (mPosLifeList.contains(index))
        return remLife(mPosLifeList.value(index));
    else
        return false;
}

bool LifeEngine::remLife(Life *life)
{
    return mLifeList.removeOne(life);
}

QList<Life*> LifeEngine::lifes() const
{
    return mLifeList;
}

QList<Life *> LifeEngine::lifes(const QString &name) const
{
    return mNamedLifeList.value(name);
}

QList<Gene> LifeEngine::genes(const QString &name, const QString &lifeName) const
{

    return mNamedGeneList[lifeName][name];
}

void LifeEngine::clear()
{
    mLifeList.clear();
    mPosLifeList.clear();
    mNamedLifeList.clear();
    mNamedGeneList.clear();
    emit changed();

}
void LifeEngine::run(int iteration)
{
    //    int currentStep = 0;

    //    while (currentStep < iteration)
    //    {
    //        step();
    //        qDebug()<<currentStep<<" pop"<<population();
    //        currentStep++;

    //    }

    //    qDebug()<<"end of simulation";

}

void LifeEngine::step()
{
    QList<Life*> temp = mLifeList;
    QList<Life*>::iterator it = temp.begin();
    QList<Life*>::iterator end = temp.end();

    int total = temp.count();
    int now   = 0;
    while (it != end) {

        Life * currentLife = *it;
        bool isLive = mScriptEngine->evaluateLife(currentLife);
        if (!isLive){
            mLifeList.removeOne(*it);
            it = temp.erase(it);
        }
        else it++;
        emit progress(qRound(float(now)*100/float(total)), QString("computing life %1").arg(now));
        ++now;

    }
    emit progress(99,"Making cache");
    makeCache();
    emit progress(0);
    emit changed();

    qDebug()<<"crash after";
}

void LifeEngine::makeSimulation(const QString &dirName, int iteration)
{


}

void LifeEngine::makeCache()
{
    mPosLifeList.clear();
    foreach (Life * life, mLifeList)
    {
        int index =  mColumns * life->x() + life->y();
        mPosLifeList.insert(index, life);
        mNamedLifeList[life->name()].append(life);
        foreach (Gene gene, life->genom().genes())
            mNamedGeneList[life->name()][gene.name()].append(gene);
    }

}




int LifeEngine::population()
{
    return mLifeList.count();
}


bool LifeEngine::load(const QString &filename)
{
    mLifeList.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    clear();
    QByteArray array = file.readAll();
    emit progress(1,"uncompressing");
    array = qUncompress(array);

    QVariant data = QxtJSON::parse(QString::fromUtf8(array));
    QVariantList lifeList = data.toMap().value("lifes").toList();

    int total = lifeList.count();
    int now   = 0;
    foreach (QVariant lifeData, lifeList)
    {
        Life * life = new Life;
        Life::parse(QxtJSON::stringify(lifeData),life);
        addLife(life);

        emit progress(qRound(float(now)*100/float(total)),"loading");
        ++now;
    }
    file.close();

    emit progress(99,"making cache");
    makeCache();
    emit progress(0);
    return true;
}

bool LifeEngine::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QVariantList lifeList;
    int total = lifes().count();
    int now   = 0;
    foreach (Life * l, lifes()){
        lifeList.append(QxtJSON::parse(Life::serialize(l)));
        emit progress(qRound(float(now)*100/float(total)),"saving");
        ++now;
    }



    QVariantMap globalMap;
    globalMap.insert("date",QDateTime::currentDateTime().toString("dd:MM:yyyy hh:mm"));
    globalMap.insert("lifes", lifeList);

    QByteArray array = QxtJSON::stringify(globalMap).toUtf8();
    emit progress(100,"compressing");
    file.write(qCompress(array,9));
    file.close();
    emit progress(99,"making cache");
    makeCache();
    emit progress(0);
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

    int index =  columns() * x + y;
    if (mPosLifeList.contains(index)){
        return true;
    }
    return false;

}

Life *LifeEngine::life(int x, int y)
{
    int index =  mColumns * x + y;
    if (mPosLifeList.contains(index))
        return mPosLifeList[index];
    else
        return NULL;
}

QObject *LifeEngine::lifeAt(int x, int y)
{
    Life * lf = life(x,y);
    if (lf)
        return new LifeObject(lf);
    else
        return NULL;
}


int LifeEngine::geneCount(const QString &geneName, const QString &lifeName) const
{
    //    int pop = 0;
    //    foreach (Life * life, lifes())
    //    {
    //        if (life->name() == lifeName)
    //        {
    //            if (life->contains(geneName))
    //                pop++;
    //        }
    //    }
    //    return pop;
}

double LifeEngine::genesMeans(const QString &geneName, const QString &lifeName)
{

    //    int total = 0;
    //    int value = 0;
    //    foreach (Life * life, lifes())
    //    {
    //        if (life->name() == lifeName)
    //        {
    //            if (life->contains(geneName))
    //            {
    //                total++;
    //                value += life->gene(geneName).value();
    //            }
    //        }
    //    }

    //    return double(value)/double(total);


}

double LifeEngine::genesVariance(const QString &geneName, const QString &lifeName)
{
    //    double means = genesMeans(geneName,lifeName);
    //    double sum   = 0;
    //    double total = 0;
    //    foreach (Life * life, lifes())
    //    {
    //        if (life->name() == lifeName)
    //        {
    //            if (life->contains(geneName)) {
    //                sum += (life->gene(geneName).value() - means) * (life->gene(geneName).value() - means);
    //                total++;
    //            }
    //        }
    //    }

    //    return sqrt(sum / (total-1));


}



QPixmap LifeEngine::toPixmap() const
{
    QPixmap pix(mRows,mColumns);
    pix.fill(Qt::white);
    QPainter paint;
    paint.begin(&pix);
    foreach (Life * life,lifes())
    {
        if (lifeFilter().contains(life->name()))
        {
            QColor col = Qt::black;
            foreach (Gene gene, life->genom().genes())
            {
                if (geneFilter().contains(gene.name()))
                    col = gene.color();
            }
            paint.setPen(QPen(col));
            paint.drawPoint(life->x(), life->y());
        }
    }
    paint.end();
    return pix;
}

int LifeEngine::count() const
{
    return mLifeList.count();
}

int LifeEngine::count(const QString &lifeName) const
{
    return mNamedLifeList[lifeName].count();
}

const QStringList &LifeEngine::lifeNames() const
{
    return mNamedLifeList.keys();
}

const QStringList &LifeEngine::geneNames(const QString &lifeName) const
{
    return mNamedGeneList[lifeName].keys();
}

const QStringList &LifeEngine::lifeFilter() const
{
    return mLifeFilter;
}

const QStringList &LifeEngine::geneFilter() const
{
    return mGeneFilter;
}

void LifeEngine::setLifeFilter(const QStringList &names)
{
    mLifeFilter = names;
}

void LifeEngine::setGeneFilter(const QStringList &names)
{
    mGeneFilter = names;
}


