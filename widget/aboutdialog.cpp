#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QApplication>
#include <QDateTime>
AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->logoLabel->setPixmap(QPixmap(":folder.png"));
    QString data;
    data += "<b>"+qApp->applicationName()+" "+
            qApp->applicationVersion()+"</b><br/>";
    data += "Copyright 2008-2012 Labsquare Organization. GPL3 Licence";




    ui->infoLabel->setText(data);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
