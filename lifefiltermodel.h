#ifndef LIFEFILTERMODEL_H
#define LIFEFILTERMODEL_H

#include <QAbstractTableModel>
#include "lifeengine.h"
class LifeFilterModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LifeFilterModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    void setLifeEngine(LifeEngine * engine);

protected:

    
signals:
    
public slots:
    void refresh();
    
private:
    LifeEngine * mEngine;
    QHash<QString, QString> mGeneSelected;
    QList<int> mLifeDisabled;
    QStringList mHeaderNames;


};

#endif // LIFEFILTERMODEL_H
