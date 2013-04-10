#include "lifedialog.h"
#include "ui_lifedialog.h"
#include <QFormLayout>
LifeDialog::LifeDialog(Life *life, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QGroupBox * groupBox = new QGroupBox;
    mAgeSpinBox = new QSpinBox;
    mNameEdit = new QLineEdit;
    mXSpinBox = new QSpinBox;
    mYSpinBox = new QSpinBox;

    mNameEdit->setPlaceholderText("Name");
    mAgeSpinBox->setPrefix("age: ");
    mXSpinBox->setPrefix("x: ");
    mYSpinBox->setPrefix("y: ");
    mGenomView = new GenomView(life);
    QWidget * coordWidget = new QWidget;
    coordWidget->setLayout(new QHBoxLayout);
    coordWidget->layout()->setMargin(0);
    coordWidget->layout()->addWidget(mXSpinBox);
    coordWidget->layout()->addWidget(mYSpinBox);

    layout->addWidget( mNameEdit);
    layout->addWidget( mAgeSpinBox);
    layout->addWidget( coordWidget);

    groupBox->setLayout(layout);
    groupBox->setTitle("property");

    QGroupBox * genomGroupBox = new QGroupBox;
    genomGroupBox->setTitle("genom");
    genomGroupBox->setLayout(new QVBoxLayout);
    genomGroupBox->layout()->addWidget(mGenomView);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(4,4,4,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(genomGroupBox);
    setLayout(mainLayout);

    //mLife = life;
    //load();

}

LifeDialog::~LifeDialog()
{
}

void LifeDialog::load()
{

    //    ui->genomTreeWidget->clear();
    //    ui->spinBox_age->setValue(mLife->age());
    //    ui->spinBox_x->setValue(mLife->x());
    //    ui->spinBox_y->setValue(mLife->y());



    //    foreach (Gene  gene, mLife->genom().genes())
    //    {

    //        QTreeWidgetItem * item  = new QTreeWidgetItem;
    //        QPixmap icon(16,16);
    //        icon.fill(gene.color());
    //        item->setText(0,gene.name());
    //        item->setIcon(0,QIcon(icon));

    //        ui->genomTreeWidget->addTopLevelItem(item);

    //        QSpinBox * valueBox = new QSpinBox(this);
    //        QSpinBox * minBox = new QSpinBox(this);
    //        QSpinBox * maxBox = new QSpinBox(this);
    //        QDoubleSpinBox * probaBox = new QDoubleSpinBox(this);
    //        QSpinBox * varianceBox = new QSpinBox(this);

    //        valueBox->setValue(gene.value());
    //        minBox->setValue(gene.min());
    //        maxBox->setValue(gene.max());
    //        probaBox->setValue(gene.mutationProbability());
    //        varianceBox->setValue(gene.variance());

    //        valueBox->setRange(gene.min(),gene.max());
    //        minBox->setRange(-10000,10000);
    //        maxBox->setRange(-10000,10000);
    //        probaBox->setRange(0,1);
    //        probaBox->setSingleStep(0.01);
    //        varianceBox->setRange(-10000,10000);


    //        ui->genomTreeWidget->setItemWidget(item,1,valueBox);
    //        ui->genomTreeWidget->setItemWidget(item,2,minBox);
    //        ui->genomTreeWidget->setItemWidget(item,3,maxBox);
    //        ui->genomTreeWidget->setItemWidget(item,4,probaBox);
    //        ui->genomTreeWidget->setItemWidget(item,5,varianceBox);


    //    }




}

void LifeDialog::save()
{

    //    mLife->setAge(ui->spinBox_age->value());
    //    mLife->setPos(ui->spinBox_x->value(), ui->spinBox_y->value());

    //    for ( int i=0; i<ui->genomTreeWidget->topLevelItemCount(); ++i)
    //    {

    //        QTreeWidgetItem * item = ui->genomTreeWidget->topLevelItem(i);

    //        QSpinBox * valueBox = qobject_cast<QSpinBox*>(ui->genomTreeWidget->itemWidget(item,1));
    //        QSpinBox * minBox = qobject_cast<QSpinBox*>(ui->genomTreeWidget->itemWidget(item,2));
    //        QSpinBox * maxBox = qobject_cast<QSpinBox*>(ui->genomTreeWidget->itemWidget(item,3));
    //        QDoubleSpinBox * probaBox = qobject_cast<QDoubleSpinBox*>(ui->genomTreeWidget->itemWidget(item,4));
    //        QSpinBox * varianceBox = qobject_cast<QSpinBox*>(ui->genomTreeWidget->itemWidget(item,5));


    //        mLife->gene(item->text(0)).setValue(valueBox->value());
    //        mLife->gene(item->text(0)).setLimit(minBox->value(), maxBox->value());
    //        mLife->gene(item->text(0)).setMutationProbability(probaBox->value());
    //        mLife->gene(item->text(0)).setVariance(varianceBox->value());



    //    }


    //    accept();



}
