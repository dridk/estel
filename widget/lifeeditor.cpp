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
    mCurrentStep = 0;
    setWindowTitle("no name");
    canBeSaved(false);
    connect(ui->scriptEdit,SIGNAL(textChanged()),this,SLOT(canBeSaved()));

    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->actionAddGene,SIGNAL(triggered()),this,SLOT(addGene()));
    connect(ui->actionEditGene,SIGNAL(triggered()),this,SLOT(editGene()));
    connect(ui->actionRemGene,SIGNAL(triggered()),this,SLOT(remGene()));
    connect(ui->actionSimReset,SIGNAL(triggered()),this,SLOT(reset()));
    connect(ui->actionSimStep,SIGNAL(triggered()),this,SLOT(step()));




}
LifeEditor::~LifeEditor()
{
    delete ui;
}
void LifeEditor::newFile()
{

    setWindowTitle("no name");
    ui->geneTreeWidget->clear();
    ui->scriptEdit->clear();
}

void LifeEditor::openFile(const QString &name)
{
    QString fileName = name;
    if (fileName.isEmpty())
    fileName = QFileDialog::getOpenFileName(this,tr("Open Life script"),
                                         "", tr("Life Script (*.json *.life"));


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

void LifeEditor::saveFile()
{
    QString fileName = windowTitle();
    if (!QFile::exists(fileName))
    {
        fileName = QFileDialog::getSaveFileName(this,tr("Save Life script"),
                                                "", tr("Life Script (*.json *.life"));

    }

    mCurrentLife->setScript(ui->scriptEdit->toPlainText());
    if(!mCurrentLife->saveFile(fileName))
    {
        QMessageBox::warning(this,"error","cannot save life");
        return;
    }
    setWindowTitle(fileName);
    canBeSaved(false);
}

void LifeEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Life script"),
                                                    "", tr("Life Script (*.json *.life"));

    mCurrentLife->setScript(ui->scriptEdit->toPlainText());
    if(!mCurrentLife->saveFile(fileName))
    {
        QMessageBox::warning(this,"error","cannot save life");
        return;
    }
    setWindowTitle(fileName);
    canBeSaved(false);
}
void LifeEditor::addGene()
{
    GeneDialog * dialog = new GeneDialog;
    if (dialog->exec() ==QDialog::Accepted)
    {
        qDebug()<<"Accepted";
        Gene g = dialog->gene();
        mCurrentLife->addGene(g);
    }

    refresh();
}

void LifeEditor::editGene()
{
}

void LifeEditor::remGene()
{

}

void LifeEditor::reset()
{
    qDebug()<<"RESET"<<mEngine->population();
    mEngine->clear();
    ui->debugTextEdit->clear();
    ui->errorTextEdit->clear();
    mCurrentStep=0;

}

void LifeEditor::step()
{
    if (mEngine->population() == 0)
    {
        mCurrentLife->setAge(0);
        mCurrentLife->setPos(0,0);
        mEngine->addLife(mCurrentLife);
    }

    mEngine->step();
    mCurrentStep++;

    ui->errorTextEdit->appendPlainText(mEngine->lastError());
    ui->debugTextEdit->appendHtml("<b>==Step:"+QString::number(mCurrentStep)+"=="
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

