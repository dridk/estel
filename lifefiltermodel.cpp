#include "lifefiltermodel.h"

LifeFilterModel::LifeFilterModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    mEngine = NULL;
    mHeaderNames <<"Lifes"<<"Genes";

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

    if (role == Qt::CheckStateRole)
    {
        if (index.column() == 0)
        {
            if (mLifeDisabled.contains(index.row()))
                return Qt::Unchecked;
            else
                return Qt::Checked;


        }
    }
    
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

    if ( index.column() == 0 && role == Qt::CheckStateRole)
    {

        if (mLifeDisabled.contains(index.row())) {
            mLifeDisabled.removeAll(index.row());
            return true;
        }
        else
        {
            mLifeDisabled.append(index.row());
            return true;
        }
    }


    return false;

}


Qt::ItemFlags LifeFilterModel::flags(const QModelIndex &index) const
{
    if (index.column() == 1)
        return Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable;

    if ( index.column() == 0)
        return Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemNeverHasChildren;


    return QAbstractTableModel::flags(index);

}

QVariant LifeFilterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return mHeaderNames.at(section);
    }

    return QVariant();
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


