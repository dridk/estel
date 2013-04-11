#include "gene.h"
#include <QDebug>
#include <QColor>
Gene::Gene(const QString& name, int val, int min, int max, int var, double proba)

{
    mName = name;
    setRange(min,max);
    setVariance(var);
    setMutationProbability(proba);
    setValue(val);
    mRootColor = Qt::white;
}
Gene::Gene(int val)
{
    mName = "unknown-gene";
    setRange(0,100);
    setVariance(1);
    setMutationProbability(0);
    setValue(val);
    mRootColor = Qt::white;
}
Gene::Gene(const Gene & other)
{
    setName(other.name());
    setMutationProbability(other.mutationProbability());
    setRange(other.min(),other.max());
    setVariance(other.variance());
    setValue(other.value());
    setRootColor(other.rootColor());
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

    int R = qrand()%mutationRate();
    qDebug()<<"R"<<R;

    if (!R)
    {
        bool sign = qrand()%2;
        int newval  = sign ? value() - variance() : value() + variance();
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
    mValue = qBound(min(),val,max());
    generateColor();
}

void Gene::setRange(int min, int max)
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

void Gene::setRootColor(const QColor &col)
{
    mRootColor = col;
    generateColor();
}


void Gene::debug()
{
    qDebug()<<name()<<"="<<value()<<"["<<min()<<"-"<<max()<<"] {"<<mutationProbability()<<"?"<<variance()<<"}";
}

const QColor &Gene::color() const
{
    return mColor;
}

const QColor &Gene::rootColor() const
{
    return mRootColor;
}
void Gene::generateColor()
{
    int sat = 255 * mValue / (mMax - mMin);

    sat = qBound(0,sat,255);
    mColor = mRootColor;
    mColor.setHsv(mColor.hue(),mColor.saturation(),sat);

}

void Gene::operator =(int v)
{
    setValue(v);
}
