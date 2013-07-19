#ifndef LIFEFILTERDELEGATE_H
#define LIFEFILTERDELEGATE_H

#include <QStyledItemDelegate>
#include "lifeengine.h"
class LifeFilterDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LifeFilterDelegate(QObject *parent = 0);


    virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    
    void setLifeEngine(LifeEngine * engine);

private:
    LifeEngine * mEngine;

};

#endif // LIFEFILTERDELEGATE_H
