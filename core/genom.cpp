#include "genom.h"
#include <QDebug>
#include <cmath>
Genom::Genom()
{

}
Genom Genom::muted() const
{
    Genom mutGenom = *this;
    mutGenom.mutate();
    return mutGenom;
}

void Genom::mutate()
{
    foreach (QString key, mGenes.keys()){
        mGenes[key].mutate();
    }
}

void Genom::add(Gene gene)
{
    if ( mGenes.contains(gene.name()))
    {
        qDebug()<<"gene "<<gene.name()<<" already exists in genom";
        return;
    }
    mGenes.insert(gene.name(),gene);
}

void Genom::rem(Gene gene)
{
    mGenes.remove(gene.name());
}

Gene& Genom::gene(const QString &name)
{
    return mGenes[name];
}
int Genom::count() const
{
    return mGenes.count();
}

int Genom::varianceSum() const
{
    int sum = 0;
    foreach (Gene  g, mGenes.values())
        sum+= g.variance();
    return sum;

}

double Genom::mutationProbabilitySum() const
{
    double sum = 0;
    foreach (Gene  g, mGenes.values()){
        sum+= g.mutationProbability();
    }
    return sum;
}
void Genom::clear()
{
    mGenes.clear();
}



void Genom::debug() const
{

    foreach (Gene gene, genes())
        gene.debug();

}

QString Genom::identity() const
{

    long key=0;

    for (int i=0; i<count(); ++i)
        key += pow(10,i)*mGenes.values()[i].value();

    QString hex = QString::number(key,16);

    return hex;
}




