#include "lifeeditor.h"
#include "ui_lifeeditor.h"
#include <QDebug>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include "qxtjson.h"
LifeEditor::LifeEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeEditor)
{
    ui->setupUi(this);
    mEngine = new LifeEngine;
    mCurrentLife = new Life;
    setWindowTitle("no name");
    canBeSaved(false);
    connect(ui->scriptEdit,SIGNAL(textChanged()),this,SLOT(canBeSaved()));

}

LifeEditor::~LifeEditor()
{
    delete ui;
}

void LifeEditor::on_actionNew_triggered()
{

    setWindowTitle("no name");
    ui->geneTreeWidget->clear();
    ui->scriptEdit->clear();


}

void LifeEditor::on_actionOpen_triggered()
{
    QString fileName =
            QFileDialog::getOpenFileName(this,
                                         tr("Open Life script"), "", tr("Life Script (*.json *.life"));

    if (!mCurrentLife->loadFile(fileName))
    {
        qDebug()<<"cannot load life";
        return;
    }

    ui->scriptEdit->setPlainText(mCurrentLife->script());
    refresh();
    setWindowTitle(fileName);
    canBeSaved(false);
}

void LifeEditor::on_actionSave_triggered()
{
    QString fileName = windowTitle();
    if (!QFile::exists(fileName))
    {
        fileName = QFileDialog::getSaveFileName(this,
                                                tr("Save Life script"), "", tr("Life Script (*.json *.life"));

    }

    mCurrentLife->setScript(ui->scriptEdit->toPlainText());
    if(!mCurrentLife->saveFile(fileName))
    {
        qDebug()<<"cannot save life...";
        return;
    }
    setWindowTitle(fileName);
    canBeSaved(false);

}

void LifeEditor::on_actionNewGene_triggered()
{

    GeneDialog * dialog = new GeneDialog;
    if (dialog->exec() ==QDialog::Accepted)
    {
        qDebug()<<"Accepted";
        Gene g = dialog->gene();
        mCurrentLife->addGene(g);
    }

}

void LifeEditor::on_actionEditGene_triggered()
{
}

void LifeEditor::on_actionRemGene_triggered()
{

}

void LifeEditor::on_actionSimReset_triggered()
{
    qDebug()<<"RESET"<<mEngine->population();
    mEngine->clear();
    ui->debugTextEdit->clear();
    ui->errorTextEdit->clear();

}

void LifeEditor::on_actionSimStep_triggered()
{
    if (mEngine->population() == 0)
    {
       mCurrentLife->setAge(0);
       mCurrentLife->setPos(0,0);
       mEngine->addLife(mCurrentLife);
    }

    mEngine->step();

    ui->errorTextEdit->appendPlainText(mEngine->lastError());
    ui->debugTextEdit->appendHtml("<b>==Step:"+QString::number(mEngine->currentStep())+"=="
                                  "Pop :"+QString::number(mEngine->population())+"==</b>");

    ui->debugTextEdit->appendPlainText(mEngine->lastDebug());





}

void LifeEditor::canBeSaved(bool enable)
{
    ui->actionSave->setEnabled(enable);
}

void LifeEditor::refresh()
{
    ui->geneTreeWidget->clear();
    foreach (Gene g, mCurrentLife->genom().genes())
    {

        QTreeWidgetItem * item = new QTreeWidgetItem;

        QString v = QString::number(g.value());
        v.append("["+QString::number(g.min())+"-"+QString::number(g.max())+"]");
        v.append("{"+QString::number(g.mutationProbability())+"±"+QString::number(g.variance())+"}");
        item->setText(0,g.name());
        item->setText(1,v);
        item->setTextColor(1,Qt::lightGray);
        ui->geneTreeWidget->addTopLevelItem(item);

    }

    ui->dockWidget->setWindowTitle("genom id :"+mGenes.identity());

}

