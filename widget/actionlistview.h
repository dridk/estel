#ifndef ACTIONLISTVIEW_H
#define ACTIONLISTVIEW_H

#include <QTreeView>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QListView>
class ActionListView : public QWidget
{
    Q_OBJECT
public:
    explicit ActionListView(QWidget *parent = 0);

    int selectionCount() const;
    int currentRow() const;
    QListView * view() {return mView;}

    QAction * addAction() const {return mAddAction;}
    QAction * editAction() const {return mEditAction;}
    QAction * remAction() const {return mRemAction;}
    QAction * refreshAction() const {return mRefreshAction;}


public slots:
    virtual void refresh();
    virtual void add();
    virtual void edit();
    virtual void remove();
    void showMessage(const QString& msg);

signals:
    void changed();

    

private:
    QListView * mView;
    QToolBar * mToolBar;

    QAction * mAddAction;
    QAction * mEditAction;
    QAction * mRemAction;
    QAction * mRefreshAction;



    
};

#endif // ACTIONLISTVIEW_H
