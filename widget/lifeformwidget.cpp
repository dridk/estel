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

#include "lifeformwidget.h"
#include <QVBoxLayout>
#include <QFrame>
LifeFormWidget::LifeFormWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QFrame * groupBox = new QFrame;
    mAgeSpinBox = new QSpinBox;
    mNameEdit = new QLineEdit;
    mXSpinBox = new QSpinBox;
    mYSpinBox = new QSpinBox;

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

    setLayout(mainLayout);


}

void LifeFormWidget::setLife(const Life &life)
{
    mLife = life;
    mNameEdit->setText(life.name());
    mAgeSpinBox->setValue(life.age());
    mXSpinBox->setValue(life.x());
    mYSpinBox->setValue(life.y());
    mXSpinBox->setRange(0, life.engine()->rows());
    mYSpinBox->setRange(0,life.engine()->columns());
    Genom genom = life.genom();
    mGenomView->setGenom(genom);

}

const Life &LifeFormWidget::life()
{
    mLife.setName(mNameEdit->text());
    mLife.setAge(mAgeSpinBox->value());
    mLife.setX(mXSpinBox->value());
    mLife.setY(mYSpinBox->value());
    mLife.setGenom(mGenomView->genom());
    return mLife;

}
