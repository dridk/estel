#ifndef JSONMODEL_H
#define JSONMODEL_H

#include <QStandardItemModel>
#include <QUrl>
class JsonModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit JsonModel(const QUrl& url = QUrl(),QObject *parent = 0);

   public slots:
    bool setData(const QString& data);
   QList<QStandardItem*> addItem(const QVariant& data);
    
};

#endif // JSONMODEL_H
