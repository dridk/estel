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


    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    QVariant data = QxtJSON::parse(file.readAll());


    QVariantList genom = data.toMap().value("genom").toList();
    mGenes.clear();
    foreach (QVariant geneData, genom)
    {
        Gene gene;
        gene.setName(geneData.toMap().value("name").toString());
        gene.setValue(geneData.toMap().value("value").toInt());
        gene.setLimit(geneData.toMap().value("min").toInt(),
                      geneData.toMap().value("max").toInt());
        gene.setVariance(geneData.toMap().value("variance").toInt());
        gene.setMutationProbability(geneData.toMap().value("proba").toDouble());

        mGenes.add(gene);

    }



    QString scriptFileName = data.toMap().value("script").toString();

    QFile scriptFile(scriptFileName);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    ui->scriptEdit->setPlainText(scriptFile.readAll());


    scriptFile.close();
    file.close();
    refresh();
    setWindowTitle(file.fileName());
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

    QFile descFile(fileName);
    if (!descFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QFileInfo fileInfo(fileName);

    QVariantMap dataMap;
    dataMap.insert("name", fileInfo.baseName());
    dataMap.insert("script", fileInfo.baseName()+"_script.js");

    QVariantList geneList;
    foreach (Gene  gene, mGenes.genes())
    {
        QVariantHash gMap;
        gMap.insert("name",gene.name());
        gMap.insert("value",gene.value());
        gMap.insert("min",gene.min());
        gMap.insert("max",gene.max());
        gMap.insert("proba",gene.mutationProbability());
        gMap.insert("variance",gene.variance());
        geneList.append(gMap);
    }

    dataMap.insert("genom", geneList);

    QString data = QxtJSON::stringify(dataMap);
    descFile.write(data.toUtf8());
    descFile.close();

    //========= save script ============

    QString scriptFileName = fileInfo.path()+QDir::separator()+fileInfo.baseName()+"_script.js";
    qDebug()<<"script saved"<<scriptFileName;
    QFile scriptFile(scriptFileName);
    if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    scriptFile.write(ui->scriptEdit->toPlainText().toUtf8());
    scriptFile.close();
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
        mGenes.add(g);
        canBeSaved();
        refresh();
    }

}

void LifeEditor::on_actionEditGene_triggered()
{
}

void LifeEditor::on_actionRemGene_triggered()
{
  foreach (QTreeWidgetItem * item, ui->geneTreeWidget->selectedItems())
    mGenes.rem(item->text(0));
  refresh();
}

void LifeEditor::on_actionSimReset_triggered()
{
    qDebug()<<"RESET"<<mEngine->population();
    mEngine->clear();
}

void LifeEditor::on_actionSimStep_triggered()
{

    if (mEngine->population() == 0)
    {
        Life * life = new Life;
        life->setScript(ui->scriptEdit->toPlainText());
        mEngine->addLife(life);
    }

    qDebug()<<"population "<<mEngine->population();
    mEngine->lifes().first()->debug();
    mEngine->step();


}

void LifeEditor::canBeSaved(bool enable)
{
    ui->actionSave->setEnabled(enable);
}

void LifeEditor::refresh()
{
    ui->geneTreeWidget->clear();
    foreach (Gene g, mGenes.genes())
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

