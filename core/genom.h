#ifndef GENOM_H
#define GENOM_H
#include <QHash>
#include "gene.h"
class Genom
{
public:
    Genom();
    Genom muted() const;
    void mutate();

    void add(Gene * gene);
    void rem(Gene * gene);
    const QList<Gene*> genes()const{return mGenes;}
    int count() const;
    int varianceSum() const;
    double mutationProbabilitySum() const;

    void clear();
    Gene * gene(int index) const;
    Gene *	operator[] ( int index ) ;
    void debug() const;

private:
    QList<Gene*> mGenes;
};

#endif // GENOM_H
