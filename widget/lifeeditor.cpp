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
    ui->dockWidget->setWidget(mGenomView);
    ui->structView->setModel(mJsonModel);
    ui->menuGenom->addActions(mGenomView->actions());
    connect(ui->scriptEdit,SIGNAL(textChanged()),this,SLOT(workHasChanged()));
    connect(mGenomView,SIGNAL(changed()),this,SLOT(workHasChanged()));

    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    connect(ui->actionSaveAs,SIGNAL(triggered()),this,SLOT(saveAs()));

    connect(ui->actionSimReset,SIGNAL(triggered()),this,SLOT(reset()));
    connect(ui->actionSimStep,SIGNAL(triggered()),this,SLOT(step()));

    connect(ui->actionUndo,SIGNAL(triggered()),ui->scriptEdit,SLOT(undo()));
    connect(ui->actionCut,SIGNAL(triggered()),ui->scriptEdit,SLOT(cut()));
    connect(ui->actionCopy,SIGNAL(triggered()),ui->scriptEdit,SLOT(copy()));
    connect(ui->actionPast,SIGNAL(triggered()),ui->scriptEdit,SLOT(paste()));
    connect(ui->actionSelectAll,SIGNAL(triggered()),ui->scriptEdit,SLOT(selectAll()));


}
LifeEditor::~LifeEditor()
{
    delete ui;
}
void LifeEditor::newFile()
{
    if (ui->actionSave->isEnabled())
    {
        QMessageBox * box = new QMessageBox;
        box->setWindowTitle("Warning");
        box->setIcon(QMessageBox::Warning);
        box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        box->setText("Do you want to save your current work ?");

        if (box->exec() == QMessageBox::Yes)
            saveFile();
    }

    setWindowTitle("Life Editor");
    ui->scriptEdit->clear();
    mCurrentLife->clearGene();
    mGenomView->refresh();
    ui->actionSave->setEnabled(false);

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
    ui->actionSave->setEnabled(false);
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
    ui->actionSave->setEnabled(false);
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
    ui->actionSave->setEnabled(false);
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
    saveFile();
    ui->tabWidget->setCurrentIndex(1);
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

void LifeEditor::workHasChanged()
{
    ui->actionSave->setEnabled(true);
}



