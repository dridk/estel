#include "lifeeditor.h"
#include "ui_lifeeditor.h"
#include <QDebug>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include "qxtjson.h"
LifeEditor::LifeEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LifeEditor)
{
    ui->setupUi(this);
    mCurrentName ="";
}

LifeEditor::~LifeEditor()
{
    delete ui;
}

void LifeEditor::on_actionNew_triggered()
{

    QString n = QInputDialog::getText(this,"life name", "type a name");
    mCurrentName = n;
    setWindowTitle(mCurrentName);

}

void LifeEditor::on_actionOpen_triggered()
{
}

void LifeEditor::on_actionSave_triggered()
{
    if (mCurrentName.isEmpty())
    {
        qDebug()<<"cannot save, create a file first";
        return;
    }

    mDescFile.setFileName(mCurrentName+".json");
    if (!mDescFile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    QVariantMap dataMap;
    dataMap.insert("name", mCurrentName);
    dataMap.insert("script", mCurrentName+"_script.js");

    QVariantList geneList;
    foreach (Gene  gene, mGenes.values())
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
    mDescFile.write(data.toUtf8());
    mDescFile.close();

    //========= save script ============

    mScriptFile.setFileName(mCurrentName+"_script.js");
    if (!mScriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    mScriptFile.write(ui->scriptEdit->toPlainText().toUtf8());

    mScriptFile.close();

}

void LifeEditor::on_actionNewGene_triggered()
{

    GeneDialog * dialog = new GeneDialog;
    if (dialog->exec() ==QDialog::Accepted)
    {
        qDebug()<<"Accepted";
        Gene g = dialog->gene();
        g.debug();
        mGenes.insert(g.name(),g);

        refresh();
    }

}

void LifeEditor::on_actionEditGene_triggered()
{
}

void LifeEditor::on_actionRemGene_triggered()
{
}

void LifeEditor::refresh()
{
    ui->geneTreeWidget->clear();
    foreach (Gene g, mGenes.values())
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

}

