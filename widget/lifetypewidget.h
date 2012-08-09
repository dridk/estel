#ifndef LIFETYPEWIDGET_H
#define LIFETYPEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include "life.h"
class LifeTypeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LifeTypeWidget(QWidget *parent = 0);
    void addLife(const Life& life);
    
signals:
    
public slots:

private:
    QListWidget * mListWidget;
    QList<Life> mLifes;
    
};

#endif // LIFETYPEWIDGET_H
