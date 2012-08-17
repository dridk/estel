#include "animmainwindow.h"
#include "ui_animmainwindow.h"
#include <QVBoxLayout>
AnimMainWindow::AnimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimMainWindow)
{
    ui->setupUi(this);
    mView = new GridView(100,100);
    mSlider = new QSlider(Qt::Horizontal);
    QVBoxLayout * layout = new QVBoxLayout;
    QWidget * widget = new QWidget;
    layout->addWidget(mView);
    layout->addWidget(mSlider);

    widget->setLayout(layout);
    setCentralWidget(widget);

}

AnimMainWindow::~AnimMainWindow()
{
    delete ui;
}
