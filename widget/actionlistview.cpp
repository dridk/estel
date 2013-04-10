#include "actionlistview.h"
#include <QVBoxLayout>
#include <QDebug>
ActionListView::ActionListView(QWidget *parent) :
    QWidget(parent)
{
    mToolBar = new QToolBar;
    mView = new QListView;
    mStatusBar = new QStatusBar;
    mToolBar->setIconSize(QSize(16,16));

    QVBoxLayout * layout  =new QVBoxLayout;
    layout->addWidget(mToolBar);
    layout->addWidget(mView);
    layout->addWidget(mStatusBar);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    mStatusBar->setSizeGripEnabled(false);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mAddAction = mToolBar->addAction(QIcon(":plus"),"add",this,SLOT(add()));
    mEditAction = mToolBar->addAction(QIcon(":edit"),"edit",this,SLOT(edit()));
    mRemAction =  mToolBar->addAction(QIcon(":delete"),"rem",this,SLOT(remove()));
    mToolBar->addWidget(spacer);


    mRefreshAction =  mToolBar->addAction(QIcon(":refresh"),"refresh",this,SLOT(refresh()));

    connect(mView,SIGNAL(doubleClicked(QModelIndex)),this,SIGNAL(doubleClicked()));
    connect(mView,SIGNAL(clicked(QModelIndex)),this,SIGNAL(clicked()));


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
    mStatusBar->showMessage(msg);
}



int ActionListView::currentRow() const
{
    if (selectionCount() == 0)
        return -1;
    return mView->selectionModel()->selectedRows().first().row();
}



