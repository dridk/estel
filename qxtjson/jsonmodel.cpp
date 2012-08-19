#include "jsonmodel.h"
#include <QDebug>
#include <QMessageBox>
#include "qxtjson/qxtjson.h"
JsonModel::JsonModel(const QUrl &url, QObject *parent):
    QStandardItemModel(parent)
{

}

bool JsonModel::setData(const QString &data)
{
    clear();
    QVariant result = QxtJSON::parse(data);

    if (result.isNull())
      return false;


    QStandardItem * root = new QStandardItem("JSON");
    root->setIcon(QIcon(":bricks.png"));

    foreach ( QStandardItem * child, addItem(result))
        root->appendRow(child);

    appendRow(root);

    return true;
}

QList<QStandardItem*>JsonModel::addItem(const QVariant &data)
{
    QList<QStandardItem*> items;

    if ( data.type() == QVariant::Map)
    {
        foreach ( QString key, data.toMap().keys())
        {
            QVariant v = data.toMap().value(key);
            QStandardItem * item = new QStandardItem(key);
            item->setIcon(QIcon(":bricks.png"));

            if (v.type() != QVariant::Map && v.type() != QVariant::List)
            {
                QIcon icon;
                if (v.type() == QVariant::Int)
                    icon = QIcon(":tag_red.png");
                else
                    icon = QIcon(":tag_green.png");
                item->setText(key+": "+v.toString());
                item->setIcon(icon);
            }

            else{
                foreach ( QStandardItem * child, addItem(v))
                    item->appendRow(child);
            }

            items.append(item);
        }
    }
    //================= LIST ========================
    if ( data.type() == QVariant::List)
    {
        for (int i=0; i<data.toList().count(); ++i)
        {
            QStandardItem * item = new QStandardItem(QString::number(i));
            item->setIcon(QIcon(":brick.png"));
            QVariant v = data.toList().value(i);

            foreach ( QStandardItem * child, addItem(v))
                item->appendRow(child);

            items.append(item);
        }
    }
    //================= OTHER ========================



    return items;



}



//QStandardItem * JsonModel::appendData(const QVariant &data)
//{
//    if ( data.type() == QVariant::Map)
//    {
//        foreach ( QString key, data.toMap().keys())
//        {
//            QStandardItem * child = new QStandardItem(key);
//            child->appendRow(appendData(data.toMap().value(key)));
//            return child;
//        }
//    }

//    return new QStandardItem("test");

////    if ( data.type() == QVariant::List)
////    {
////        for (int i=0; i<data.toList().count(); ++i)
////        {
////            QStandardItem * child = new QStandardItem(QString::number(i));
////            child->appendRow(appendData(data.toList().value(i)));
////            return child;
////        }
////    }

////    if (data.type() != QVariant::List  &&  data.type() != QVariant::Map)
////    {
////        QStandardItem * child = new QStandardItem(data.toString());
////        return child;
////    }




//}
