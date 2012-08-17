#ifndef LIFEFILEVIEW_H
#define LIFEFILEVIEW_H
#include <QStringListModel>
#include <QStandardItemModel>
#include "actionlistview.h"
#include "lifeeditor.h"

class LifeFileView : public ActionListView
{
    Q_OBJECT

public:
    LifeFileView(QWidget * parent = 0);

    const QString& filename(int row);
    const QString& currentFilename();

public slots:
    void refresh(const QString& path = QString());
    void remove();
    void edit();
    void add();
    void test();

private:
    QStandardItemModel * mModel;

};

#endif // LIFEFILEVIEW_H
