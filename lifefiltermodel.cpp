#include "lifefiltermodel.h"

LifeFilterModel::LifeFilterModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    mEngine = NULL;

}

int LifeFilterModel::rowCount(const QModelIndex &parent) const
{
    if (mEngine!=NULL)
        return mEngine->lifeNames().count();
    else
        return 0;


}
int LifeFilterModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant LifeFilterModel::data(const QModelIndex &index, int role) const
{
    if (!mEngine)
        return QVariant();
    
    if ( role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return mEngine->lifeNames().at(index.row());

        if (index.column() == 1){
            QString name = mEngine->lifeNames().at(index.row());
            return mGeneSelected[name];

        }
    }

    return QVariant();
}

bool LifeFilterModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if ( index.column() == 1 && role == Qt::EditRole)
    {

        QString lifeName = QAbstractTableModel::index(index.row(),0).data().toString();
        mGeneSelected[lifeName] = value.toString();
        return true;
    }
    return false;

}


Qt::ItemFlags LifeFilterModel::flags(const QModelIndex &index) const
{
    if (index.column() == 1)
        return Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable;
    else return QAbstractTableModel::flags(index);

}

void LifeFilterModel::setLifeEngine(LifeEngine *engine)
{
    mEngine = engine;
}

void LifeFilterModel::refresh()
{

    if (!mEngine)
        return;

    mGeneSelected.clear();
    foreach ( QString life, mEngine->lifeNames())
    {
        mGeneSelected[life] = mEngine->geneNames(life).first();

    }

    emit layoutChanged();

}


