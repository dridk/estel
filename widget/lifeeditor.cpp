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
    mGenomView = new GenomView(mCurrentLife);
    mJsonModel = new JsonModel;
    mCurrentStep = 0;
    setWindowTitle("Life Editor");
    canBeSaved(false);
    ui->dockWidget->setWidget(mGenomView);
    ui->structView->setModel(mJsonModel);
    ui->menuGenom->addActions(mGenomView->actions());
    connect(ui->scriptEdit,SIGNAL(textChanged()),this,SLOT(canBeSaved()));

    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));

    connect(ui->actionSimReset,SIGNAL(triggered()),this,SLOT(reset()));
    connect(ui->actionSimStep,SIGNAL(triggered()),this,SLOT(step()));




}
LifeEditor::~LifeEditor()
{
    delete ui;
}
void LifeEditor::newFile()
{

    setWindowTitle("Life Editor");
    ui->scriptEdit->clear();
    mCurrentLife->clearGene();
    mGenomView->refresh();

}

void LifeEditor::openFile(const QString &name)
{
    qDebug()<<"OPEN FILE";
    QString fileName = name;
    if (fileName.isEmpty())
        fileName = QFileDialog::getOpenFileName(this,tr("Open Life script"),
                                                "", tr("Life Script (*.json *.life"));

    qDebug()<<fileName;

    if (!mCurrentLife->loadFile(fileName))
    {
        qDebug()<<"cannot load life";
        return;
    }

    ui->scriptEdit->setPlainText(mCurrentLife->script());
    mGenomView->refresh();
    mJsonModel->setData(Life::serialize(mCurrentLife));
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


        QFileInfo info(fileName);
        if (info.suffix()!="life")
            fileName.append(".life");
    }

    mCurrentLife->setScript(ui->scriptEdit->toPlainText());
    if(!mCurrentLife->saveFile(fileName))
    {
        QMessageBox::warning(this,"error","cannot save life");
        return;
    }
    setWindowTitle(fileName);
    mJsonModel->setData(Life::serialize(mCurrentLife));
    canBeSaved(false);
}

void LifeEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Life script"),
                                                    "", tr("Life Script (*.json *.life"));



    QFileInfo info(fileName);
    if (info.suffix()!="life")
        fileName.append(".life");

    mCurrentLife->setScript(ui->scriptEdit->toPlainText());
    if(!mCurrentLife->saveFile(fileName))
    {
        QMessageBox::warning(this,"error","cannot save life");
        return;
    }
    setWindowTitle(fileName);
    mJsonModel->setData(Life::serialize(mCurrentLife));
    canBeSaved(false);
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



