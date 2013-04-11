#include "lifedialog.h"
#include "ui_lifedialog.h"
#include <QFormLayout>
LifeDialog::LifeDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QFrame * groupBox = new QFrame;
    mAgeSpinBox = new QSpinBox;
    mNameEdit = new QLineEdit;
    mXSpinBox = new QSpinBox;
    mYSpinBox = new QSpinBox;
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

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(genomGroupBox);
    mainLayout->addStretch();
    mainLayout->addWidget(mDialogBox);
    setLayout(mainLayout);

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
    mNameEdit->setText(life.name());
    mAgeSpinBox->setValue(life.age());
    mXSpinBox->setValue(life.x());
    mYSpinBox->setValue(life.y());

   Genom genom = life.genom();

    mGenomView->setGenom(genom);
}

 Life LifeDialog::life()
{
    Life life;
    life.setName(mNameEdit->text());
    life.setAge(mAgeSpinBox->value());
    life.setX(mXSpinBox->value());
    life.setY(mYSpinBox->value());
    life.setGenom(mGenomView->genom());
    return life;

}
