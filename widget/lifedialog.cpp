#include "lifedialog.h"
#include "ui_lifedialog.h"
#include <QFormLayout>
#include <QSplitter>
LifeDialog::LifeDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QFrame * groupBox = new QFrame;
    mAgeSpinBox = new QSpinBox;
    mNameEdit = new QLineEdit;
    mXSpinBox = new QSpinBox;
    mYSpinBox = new QSpinBox;
    mEditor = new LifeScriptEditor;
    mDialogBox = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

    setWindowIcon(QIcon(":rabbit"));

    mNameEdit->setPlaceholderText("Name");
    mAgeSpinBox->setPrefix("age: ");
    mXSpinBox->setPrefix("x: ");
    mYSpinBox->setPrefix("y: ");
    mGenomView = new GenomView;
    QWidget * coordWidget = new QWidget;
    coordWidget->setLayout(new QHBoxLayout);
    coordWidget->layout()->setMargin(0);
    coordWidget->layout()->addWidget(mXSpinBox);
    coordWidget->layout()->addWidget(mYSpinBox);

    layout->addWidget( mNameEdit);
    layout->addWidget( mAgeSpinBox);
    layout->addWidget( coordWidget);

    groupBox->setLayout(layout);
    groupBox->layout()->setMargin(0);

    QFrame * genomGroupBox = new QFrame;
    genomGroupBox->setLayout(new QVBoxLayout);
    genomGroupBox->layout()->addWidget(mGenomView);
    genomGroupBox->layout()->setMargin(0);

    QWidget * mainWidget = new QWidget;
    mainWidget->setLayout(new QVBoxLayout);
    mainWidget->layout()->setSpacing(0);
    mainWidget->layout()->addWidget(groupBox);
    mainWidget->layout()->addWidget(genomGroupBox);

    QSplitter * splitter = new QSplitter;
    splitter->addWidget(mainWidget);
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
    delete mAgeSpinBox;
    delete mNameEdit;
    delete mXSpinBox;
    delete  mYSpinBox;
    delete mGenomView;
    delete mDialogBox;


}

void LifeDialog::setLife(const Life &life)
{
    mLife = life;
    mNameEdit->setText(life.name());
    mAgeSpinBox->setValue(life.age());
    mXSpinBox->setValue(life.x());
    mYSpinBox->setValue(life.y());
    mXSpinBox->setRange(0, life.engine()->rows());
    mYSpinBox->setRange(0,life.engine()->columns());
    mEditor->setScript(life.script());
    Genom genom = life.genom();
    mGenomView->setGenom(genom);

    qDebug()<<"LIFE SCRIPT IS "<< life.script();
}

const Life& LifeDialog::life()
{

    mLife.setName(mNameEdit->text());
    mLife.setAge(mAgeSpinBox->value());
    mLife.setX(mXSpinBox->value());
    mLife.setY(mYSpinBox->value());
    mLife.setGenom(mGenomView->genom());
    mLife.setScript(mEditor->script());
    return mLife;

}
