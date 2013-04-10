#ifndef GENOM_H
#define GENOM_H
#include <QHash>
#include "gene.h"

//! \class Genom
//! \brief Genom is a container of Gene used in Life
//! It contains genes and several method to works on genes

class Genom
{
public:
    Genom();

    //! \return a muted copy genom
    Genom muted() const;

    //! \brief mute all genes inside the genom
    void mutate();

    //! \brief add gene
    void add(Gene gene);

    //! \brief add gene
    void rem(Gene gene);

    //! \return all genes in a QList
    const QList<Gene> genes()const{return mGenes.values();}

    //! \return gene by his name
    //! \param name : the name of gene
    Gene& gene(const QString& name);

    //! \return genes count
    int count() const;

    //! \return the sum of all variance in genom
    //! \brief this is an indicator of the global variance
    int varianceSum() const;

    //! \return the sum of the mutation probability
    //! \brief this is an indicator of the global mutation probability
    double mutationProbabilitySum() const;

    //! \brief check if genom contains a gene
    //! \param key : gene name
    bool contains(const QString& key) const;

    //! \brief remove all genes
    void clear();

    //! \return the hexadecimal identifier of the genom
    QString identity() const;

    void debug() const;

    Gene& operator[](const QString& name) { return mGenes[name];}

private:
    QHash<QString,Gene> mGenes;
};

#endif // GENOM_H
