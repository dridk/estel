#include "lifefileview.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
LifeFileView::LifeFileView(QWidget *parent)
    :ActionListView(parent)
{
    mModel = new QStandardItemModel(this);
    view()->setModel(mModel);

    setWindowTitle("Lifes Types");
    refresh();

    connect(this,SIGNAL(doubleClicked()),this,SLOT(edit()));


}

void LifeFileView::refresh(const QString &path)
{
    mModel->clear();
    mModel->setHorizontalHeaderLabels(QStringList()<<"Life type");
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

void LifeFileView::remove()
{
    QMessageBox * box = new QMessageBox(this);
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setDefaultButton(QMessageBox::No);
    box->setWindowTitle("Delete lifeType file");
    box->setText("Do you really want to remove this file?");

    if (box->exec() == QMessageBox::No)
        return;

    QString filename = mModel->item(currentRow())->data().toString();

    if (!QFile::remove(filename)){
        QMessageBox::warning(this,"error","cannot remove file");
        return;
    }

    refresh();
}

void LifeFileView::edit()
{
    if (!selectionCount())
        return;
    QString filename = mModel->item(currentRow())->data().toString();
    LifeEditor * editor = new LifeEditor;
    editor->openFile(filename);
    editor->setAttribute(Qt::WA_DeleteOnClose);
    connect(editor,SIGNAL(destroyed()),this,SLOT(refresh()));
    editor->show();

}

void LifeFileView::add()
{
    LifeEditor * editor = new LifeEditor;
    editor->setAttribute(Qt::WA_DeleteOnClose);
    connect(editor,SIGNAL(destroyed()),this,SLOT(refresh()));
    editor->show();


}

void LifeFileView::test()
{
    qDebug()<<"CLOSE";
}

const QString &LifeFileView::filename(int row)
{
    return mModel->item(row)->data().toString();
}

const QString &LifeFileView::currentFilename()
{
    if (!selectionCount())
        return QString();
    else
        return filename(currentRow());
}


