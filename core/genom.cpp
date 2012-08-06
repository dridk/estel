#include "genom.h"
#include <QDebug>
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
    foreach (Gene  * g , genes()){
        g->mutate();
    }
}

void Genom::add(Gene * gene)
{
    mGenes.append(gene);
}

void Genom::rem(Gene *gene)
{
    mGenes.removeOne(gene);
}
int Genom::count() const
{
    return mGenes.count();
}

int Genom::varianceSum() const
{
    int sum = 0;
    foreach (Gene  *g, mGenes)
        sum+= g->variance();
    return sum;

}

double Genom::mutationProbabilitySum() const
{
    double sum = 0;
    foreach (Gene * g, mGenes){
        sum+= g->mutationProbability();
    }
    return sum;
}
void Genom::clear()
{
    mGenes.clear();
}

Gene * Genom::gene(int index) const
{
    return mGenes.at(index);
}

Gene * Genom::operator [](int index)
{
    return mGenes.at(index);
}

void Genom::debug() const
{

    foreach (Gene *gene, genes())
        gene->debug();

}

