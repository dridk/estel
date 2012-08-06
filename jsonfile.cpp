#include "jsonfile.h"
#include <QDebug>
#include "lifeengine.h"
JsonFile::JsonFile(QObject *parent) :
    QObject(parent)
{
}

void JsonFile::open(const QString &filename)
{

    mFile.setFileName(filename);
    mFile.remove();
    if (!mFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"cannot openfile "<<mFile.errorString();
        return;
    }

    mOut.setDevice(&mFile);
    mOut<<"{\n";
    mOut<<"\"experiment\":{\n";
    mOut<<"\"date\":\"30/02/2012\",\n";
    mOut<<"\"name\":\"Sacha\",\n";
    mOut<<"\"data\":[\n";



}


void JsonFile::close()
{
    mOut<<"\n]}}";

    mFile.close();
}

void JsonFile::addStep(int step, int totalStep, LifeEngine *engine)
{

//    mOut<<"\n\n{\"step\":{\n ";
//    mOut<<"\"time\":"+QString::number(step)+",\n ";
//    mOut<<"\"population\":"+QString::number(engine->count())+",\n ";
//    mOut<<"\"lifes\":[\n";


//    for (int lifeId=0; lifeId<engine->lifes().count(); ++lifeId)
//    {
//        Life life = engine->lifes()[lifeId];
//        mOut<<"\n{";
//        mOut<<"\"x\":\""+QString::number(life.x())+"\",";
//        mOut<<"\"y\":\""+QString::number(life.y())+"\",";
//        mOut<<"\"genom\":[";



//        for (int geneId=0;geneId<life.genom().count(); ++geneId)
//        {


//            Gene * g = life.genom().gene(geneId);
//            mOut<<"{";
//            mOut<<"\"value\":"+QString::number(g->value())+",";
//            mOut<<"\"min\":"+QString::number(g->min())+",";
//            mOut<<"\"max\":"+QString::number(g->max())+",";
//            mOut<<"\"probability\":"+QString::number(g->mutationProbability())+",";
//            mOut<<"\"variance\":"+QString::number(g->variance());

//            mOut<<"}";
//            if (geneId < life.genom().genes().count() - 1)
//                mOut<<",";

//        }
//        mOut<<"]";
//        mOut<<"}";
//        if (lifeId < engine->lifes().count()-1)
//            mOut<<",";

//    }

//    mOut<<"]\n";

//    mOut<<"}}";

//    if (step < totalStep -1)
//        mOut<<",";


}
