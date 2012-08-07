#include "gene.h"
#include <QDebug>
Gene::Gene(const QString& name, int val, int min, int max, int var, double proba)

{
    mName = name;
    setLimit(min,max);
    setVariance(var);
    setMutationProbability(proba);
    setValue(val);
}
Gene::Gene(int val)
{
    mName = "unknown-gene";
    setLimit(0,1000);
    setVariance(1);
    setMutationProbability(0);
    setValue(val);
}
Gene::Gene(const Gene & other)
{
    setName(other.name());
    setMutationProbability(other.mutationProbability());
    setLimit(other.min(),other.max());
    setVariance(other.variance());
    setValue(other.value());
}
Gene Gene::muted() const
{
    Gene mutGene = *this;
    mutGene.mutate();
    return mutGene;
}

void Gene::mutate()
{
    if (!mutationProbability())
        return;

    if (!variance())
        return;


    //get the random value between 0 and 1/probability
    if (!(qrand()%mutationRate()))
    {
        int  corr =(qrand()%variance()) + 1;
        bool sign = qrand()%2;
        int newval  = sign ? value() - corr : value() + corr;
        setValue(newval);
    }
}

const QString &Gene::name() const
{
    return mName;
}

int Gene::value() const
{
    return mValue;
}

int Gene::min() const
{
    return mMin;
}

int Gene::max() const
{
    return mMax;
}
int Gene::variance() const
{
    return mVariance;
}

int Gene::mutationRate() const
{
    return mMutRate;
}

double Gene::mutationProbability() const
{
    return mMutationProbability;
}
void Gene::setValue(int val)
{
    mValue = val;
    generateColor();
}

void Gene::setLimit(int min, int max)
{
    mMin = min;
    mMax = max;

}

void Gene::setName(const QString &name)
{
    mName = name;
}

void Gene::setVariance(int var)
{
    mVariance = var;
}

void Gene::setMutationProbability(double proba)
{
    //set the mutation probability and compute the mutation rate which are 1/p
    mMutationProbability = proba;
    if (!mMutationProbability)
        mMutRate = 0;
    else
        mMutRate = 1/ mMutationProbability;
}
void Gene::debug()
{
    qDebug()<<name()<<"="<<value()<<"["<<min()<<"-"<<max()<<"] {"<<mutationProbability()<<"?"<<variance()<<"}";
}

const QColor &Gene::color() const
{
    return mColor;
}
void Gene::generateColor()
{
    int sat = 255 * mValue / (mMax - mMin);

    sat = qBound(0,sat,255);
    mColor = QColor(0,sat,0);
}

void Gene::operator =(int v)
{
    setValue(v);
}
