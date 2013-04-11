/***************************************************************************
**                                                                        **
**  FcsViewer, a simple cytometry data viewer made with Qt4 and           **
**  customplot made by Emanuel Eichhammer                                 **
**  Copyright (C) 2013 Sacha Schutz                                       **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author : Sacha Schutz                                        **
**           Website: http://www.labsquare.org                            **
**           Email  : sacha@labsquare.org                                 **
**           Date   : 12.03.12                                            **
****************************************************************************/

#include "genedialog.h"
#include <QVBoxLayout>
#include <QToolButton>
GeneDialog::GeneDialog(QWidget *parent) :
    QDialog(parent)
{
    mNameEdit     = new QLineEdit;
    mValueSpinBox = new QSpinBox;
    mMinSpinBox   = new QSpinBox;
    mMaxSpinBox   = new QSpinBox;
    mVarSpinBox   = new QSpinBox;
    mProbSpinBox  = new QDoubleSpinBox;
    mButtonBox    = new QDialogButtonBox(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
    mColorWidget  = new ColorGradientWidget;
    mColorButton  = new ColorButton;

    mNameEdit->setPlaceholderText("Gene's name");
    mValueSpinBox->setPrefix("v: ");
    mValueSpinBox->setToolTip("Value of the gene between min and max");
    mMinSpinBox->setPrefix("min: ");
    mMinSpinBox->setRange(0,1000);
    mMaxSpinBox->setPrefix("max: ");
    mMaxSpinBox->setRange(0,1000);
    mVarSpinBox->setPrefix("var: ");
    mVarSpinBox->setRange(0,1000);
    mProbSpinBox->setPrefix("prob: ");
    mProbSpinBox->setRange(0,1);
    mProbSpinBox->setSingleStep(0.01);
    mColorWidget->setColor(Qt::red);
    mColorButton->setColor(Qt::red);


    QWidget * headerWidget = new QWidget;
    headerWidget->setLayout(new QHBoxLayout);
    headerWidget->layout()->addWidget(mNameEdit);
    headerWidget->layout()->addWidget(mColorButton);
    headerWidget->layout()->setMargin(0);
    headerWidget->layout()->setAlignment(Qt::AlignTop);


    QWidget * limitWidget = new QWidget;
    limitWidget->setLayout(new QHBoxLayout);
    limitWidget->layout()->addWidget(mMinSpinBox);
    limitWidget->layout()->addWidget(mMaxSpinBox);
    limitWidget->layout()->setMargin(0);
    limitWidget->layout()->setAlignment(Qt::AlignTop);




    QVBoxLayout * mainLayout = new QVBoxLayout;

    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(mValueSpinBox);
    mainLayout->addWidget(limitWidget);
    mainLayout->addWidget(mVarSpinBox);
    mainLayout->addWidget(mProbSpinBox);
    mainLayout->addWidget(mColorWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(mButtonBox);

    setLayout(mainLayout);

    setFixedSize(minimumSize());

    connect(mMinSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setRange()));
    connect(mMaxSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setRange()));
    connect(mNameEdit,SIGNAL(textChanged(QString)),this,SLOT(nameChanged(QString)));
    connect(mButtonBox,SIGNAL(accepted()),this,SLOT(accept()));
    connect(mButtonBox,SIGNAL(rejected()),this,SLOT(reject()));
    connect(mColorButton,SIGNAL(colorChanged(QColor)),mColorWidget,SLOT(setColor(QColor)));

    setGene(Gene());


}

GeneDialog::~GeneDialog()
{
}

void GeneDialog::setGene(const Gene &gene)
{
    mGene = gene;
    mNameEdit->setText(mGene.name());
    mValueSpinBox->setValue(mGene.value());
    mMinSpinBox->setValue(mGene.min());
    mMaxSpinBox->setValue(mGene.max());
    mVarSpinBox->setValue(mGene.variance());
    mProbSpinBox->setValue(mGene.mutationProbability());
    mColorButton->setColor(mGene.rootColor());
    mColorWidget->setColor(mGene.rootColor());


}

Gene GeneDialog::gene() const
{
    Gene g;
    g.setName(mNameEdit->text());
    g.setValue(mValueSpinBox->value());
    g.setRange(mMinSpinBox->value(), mMaxSpinBox->value());
    g.setVariance(mVarSpinBox->value());
    g.setMutationProbability(mProbSpinBox->value());
    g.setRootColor(mColorButton->color());
    return g;
}

void GeneDialog::setRange()
{
    mValueSpinBox->setRange(mMinSpinBox->value(), mMaxSpinBox->value());
}

void GeneDialog::nameChanged(const QString &name)
{

    setWindowTitle(name);
    mButtonBox->button(QDialogButtonBox::Save)->setDisabled(name.isEmpty());

}
