#ifndef ACTIONLISTVIEW_H
#define ACTIONLISTVIEW_H

#include <QListView>
#include <QAction>
#include <QToolBar>
class ActionListView : public QWidget
{
    Q_OBJECT
public:
    explicit ActionListView(QWidget *parent = 0);

    QListView * view() const;

public slots:
    virtual void refresh();
    virtual void add();
    virtual void edit();
    virtual void remove();
    

private:
    QList<QAction*> mActions;
    QListView * mView;
    QToolBar * mToolBar;
    
};

#endif // ACTIONLISTVIEW_H
