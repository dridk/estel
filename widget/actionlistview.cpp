#include "actionlistview.h"
#include <QVBoxLayout>
#include <QDebug>
ActionListView::ActionListView(QWidget *parent) :
    QWidget(parent)
{
    mToolBar = new QToolBar;
    mView = new QListView;
    mToolBar->setIconSize(QSize(16,16));
    mView->setIconSize(QSize(16,16));

    QVBoxLayout * layout  =new QVBoxLayout;
    layout->addWidget(mToolBar);
    layout->addWidget(mView);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mAddAction = mToolBar->addAction(QIcon(":plus"),"add",this,SLOT(add()));
    mEditAction = mToolBar->addAction(QIcon(":edit"),"edit",this,SLOT(edit()));
    mRemAction =  mToolBar->addAction(QIcon(":delete"),"rem",this,SLOT(remove()));
    mToolBar->addWidget(spacer);


    mRefreshAction =  mToolBar->addAction(QIcon(":refresh"),"refresh",this,SLOT(refresh()));

    connect(mView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(edit()));


    mView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


int ActionListView::selectionCount() const
{
    return mView->selectionModel()->selectedRows().count();
}

void ActionListView::refresh()
{


}

void ActionListView::add()
{
}

void ActionListView::edit()
{
}

void ActionListView::remove()
{
}

void ActionListView::showMessage(const QString &msg)
{
}



int ActionListView::currentRow() const
{
    if (selectionCount() == 0)
        return -1;
    return mView->selectionModel()->selectedRows().first().row();
}



