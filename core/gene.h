#ifndef GENE_H
#define GENE_H
#include <QVariant>
#include <QColor>
#include <QDebug>
class Gene;




class Gene
{
public:
    Gene(const QString& name, int val=50, int min=0, int max=100, int var=0,double proba=0);
    Gene(int val = 1);
    Gene(const Gene&);
    Gene muted() const;
    void mutate();
    const QString& name() const;
    int value() const;
    int min() const;
    int max() const;
    int variance() const;
    int mutationRate() const;
    double mutationProbability() const;
    void setValue(int val);
    void setLimit(int min, int max);
    void setName(const QString& name);
    void setVariance(int var);
    void setMutationProbability(double proba);
    const QColor& color() const;
    void generateColor();
    void	operator= ( int v );
    void debug();


private:
    int mValue;
    int mMin,mMax;
    int mVariance;
    int mMutRate;
    double mMutationProbability;
    QString mName;
    QColor mColor;


};

#endif // GENE_H
