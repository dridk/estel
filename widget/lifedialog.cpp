#include "lifedialog.h"
#include "ui_lifedialog.h"
#include <QFormLayout>
#include <QSplitter>
LifeDialog::LifeDialog(QWidget *parent) :
    QDialog(parent)
{

    mLifeFormWidget = new LifeFormWidget;
    mEditor = new LifeScriptEditor;
    mDialogBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

    QSplitter * splitter = new QSplitter;
    splitter->addWidget(mLifeFormWidget);
    splitter->addWidget(mEditor);

    QVBoxLayout * rootLayout = new QVBoxLayout;
    rootLayout->addWidget(splitter);
    rootLayout->addStretch();
    rootLayout->addWidget(mDialogBox);
    setLayout(rootLayout);

    connect(mDialogBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(mDialogBox,SIGNAL(rejected()),this,SLOT(reject()));
}

LifeDialog::~LifeDialog()
{
    delete mEditor;
    delete mLifeFormWidget;
    delete mDialogBox;
}

void LifeDialog::setLife(const Life &life)
{
    mLife = life;
    mLifeFormWidget->setLife(life);
    mEditor->setScript(life.script());

}

const Life& LifeDialog::life()
{
    mLife = mLifeFormWidget->life();
    mLife.setScript(mEditor->script());
    return mLife;

}
