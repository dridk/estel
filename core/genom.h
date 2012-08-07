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

    void add(Gene gene);
    void rem(Gene gene);
    const QList<Gene> genes()const{return mGenes.values();}
    Gene& gene(const QString& name);
    int count() const;
    int varianceSum() const;
    double mutationProbabilitySum() const;

    void clear();
    void debug() const;

private:
    QHash<QString,Gene> mGenes;
};

#endif // GENOM_H
