#ifndef GENE_H
#define GENE_H
#include <QVariant>
#include <QColor>
#include <QDebug>

//! \class Gene
//! \brief This class contain the gene information.
//! It contains params to manage the mutation.
//! Each gene has a integer value with a range (min and max). So The
//! value cannot be out of the range. There is 2 other params to manage the mutation.
//! mutationProbability must be between 0 and 1. When a mutation appears, the new value
//! value of gene equal value+variance.

class Gene;
class Gene
{
public:
    //! \brief Gene Constructor
    //! \param name : the name of gene
    //! \param value : the value of gene
    //! \param var : the variance of mutation
    //! \param proba : the mutation probability. Should be between 0 and 1
    Gene(const QString& name, int val=50, int var=0,double proba=0);

    //! \brief Gene Constructor
    //! \param value : the value of gene
    Gene(int val = 1);

    //! \brief Copy Constructor
    Gene(const Gene&);

    //! \return a muted gene computed with mutationProbability
    //! and variance
    Gene muted() const;

    //! \brief Make a mutation on the current gene
    void mutate();

    //! \return the name of current gene
    const QString& name() const;

    //! \return the value of current gene
    int value() const;

    //! \return the variance of current gene
    //! \brief When the gene mute, the value will be increment of variancc
    int variance() const;

    //! \return mutation rate.
    //! \brief this equal 1/mutationProbability
    int mutationRate() const;

    //! \return mutation probability between 0 an 1
    //! \brief mutationProbabily equal 0, no mutation will appears
    double mutationProbability() const;

    //! \brief set the current gene value
    void setValue(int val);

    //! \brief set the current gene name
    void setName(const QString& name);

    //! \brief set the current gene variance
    void setVariance(int var);

    //! \brief set the current gene mutation probability
    void setMutationProbability(double proba);

    //! \brief set the current gene root color
    //! this color represent the gene.Each gene value will have
    //! a color in the range color of rootColor.
    //! Exemple:if color is red, then the minium value will be dark red
    //! And the maximum value will be light red
    void setRootColor(const QColor& col);

    //! \return the current gene color computed from generateColor()
    const QColor& color() const;

    //! \return the rootColor
    const QColor& rootColor() const;

    //! \brief Genere the color from the rootColor and the range values
    void generateColor();
    void	operator= ( int v );
    void debug();


private:
    int mValue;
    int mVariance;
    int mMutRate;
    double mMutationProbability;
    QString mName;
    QColor mColor;
    QColor mRootColor;


};

#endif // GENE_H
