#ifndef ACTIONLISTVIEW_H
#define ACTIONLISTVIEW_H

#include <QTreeView>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
class ActionListView : public QWidget
{
    Q_OBJECT
public:
    explicit ActionListView(QWidget *parent = 0);

    QTreeView * view() const;
    int selectionCount() const;
    int currentRow() const;


public slots:
    virtual void refresh();
    virtual void add();
    virtual void edit();
    virtual void remove();
    void showMessage(const QString& msg);
    void hideAction(int index);

signals:
    void changed();
    

private:
    QList<QAction*> mActions;
    QTreeView * mView;
    QToolBar * mToolBar;
    QStatusBar * mStatusBar;
    
};

#endif // ACTIONLISTVIEW_H
