#ifndef LIFEFILEVIEW_H
#define LIFEFILEVIEW_H
#include <QStringListModel>
#include <QStandardItemModel>
#include "actionlistview.h"
class LifeFileView : public ActionListView
{
public:
    LifeFileView(QWidget * parent = 0);
    void refresh(const QString& path = QString());

private:
    QStandardItemModel * mModel;

};

#endif // LIFEFILEVIEW_H
