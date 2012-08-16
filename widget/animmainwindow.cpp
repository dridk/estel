#include "animmainwindow.h"
#include "ui_animmainwindow.h"

AnimMainWindow::AnimMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnimMainWindow)
{
    ui->setupUi(this);
}

AnimMainWindow::~AnimMainWindow()
{
    delete ui;
}
