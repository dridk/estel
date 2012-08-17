#include "lifefileview.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
LifeFileView::LifeFileView(QWidget *parent)
    :ActionListView(parent)
{
    mModel = new QStandardItemModel(this);
    view()->setModel(mModel);

    refresh();
    setWindowTitle("Lifes Types");

}

void LifeFileView::refresh(const QString &path)
{
    mModel->clear();
    QString currentDir = path;
    if ( path.isEmpty())
        currentDir = qApp->applicationDirPath();

    QStringList filters;
    filters << "*.json"<<"*.life";

    QDir dir(currentDir);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(filters);

    foreach (QFileInfo fileInfo, dir.entryInfoList())
    {
        QStandardItem * item = new QStandardItem;
        item->setText(fileInfo.baseName());
        item->setIcon(QIcon(":file_extension_bat.png"));
        item->setData(fileInfo.filePath());
        item->setEditable(false);
        mModel->appendRow(item);
    }

}

