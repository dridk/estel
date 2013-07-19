#include "lifefilterdelegate.h"
#include <QComboBox>
LifeFilterDelegate::LifeFilterDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    mEngine = NULL;
}

QWidget * LifeFilterDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 1) {
        if (mEngine)
        {
             QString lifeName  = index.model()->index(index.row(),0).data().toString();
            QComboBox * box = new QComboBox(parent);
            foreach (QString geneName , mEngine->geneNames(lifeName))
            {
                box->addItem(geneName);
            }

           return box;
        }
    }

    else
        return QStyledItemDelegate::createEditor(parent,option,index);
}

void LifeFilterDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 1)
    {
        QComboBox  * box = qobject_cast<QComboBox*>(editor);
        box->setCurrentText(index.data().toString());
    }

}

void LifeFilterDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    if (index.column() == 1)
    {
        QComboBox  * box = qobject_cast<QComboBox*>(editor);
        model->setData(index,box->currentText());
    }
}

void LifeFilterDelegate::setLifeEngine(LifeEngine *engine)
{
    mEngine = engine;
}
