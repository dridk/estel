#include "actionlistview.h"
#include <QVBoxLayout>
#include <QDebug>
ActionListView::ActionListView(QWidget *parent) :
    QWidget(parent)
{
    mToolBar = new QToolBar;
    mView = new QTreeView;
    mStatusBar = new QStatusBar;

    QVBoxLayout * layout  =new QVBoxLayout;
    layout->addWidget(mToolBar);
    layout->addWidget(mView);
    layout->addWidget(mStatusBar);
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    mToolBar->addAction(QIcon(":brick_add.png"),"add",this,SLOT(add()));
    mToolBar->addAction(QIcon(":brick_edit.png"),"edit",this,SLOT(edit()));
    mToolBar->addAction(QIcon(":brick_delete.png"),"rem",this,SLOT(remove()));
    mToolBar->addWidget(spacer);

    mToolBar->addAction(QIcon(":arrow_refresh.png"),"refresh",this,SLOT(refresh()));


}

QTreeView *ActionListView::view() const
{
    return mView;
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
