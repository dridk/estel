#include "gridview.h"
#include <QVBoxLayout>
#include <QToolBar>
GridView::GridView(int row, int column, QWidget *parent):
    QScrollArea(parent)
{
    mGridWidget = new GridWidget(row,column);
    setWidget(mGridWidget);


}

GridView::~GridView()
{
    delete mGridWidget;

}

GridWidget *GridView::grid()
{
    return mGridWidget;
}
