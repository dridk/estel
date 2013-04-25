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

#include "bottomtoolbar.h"
#include <QAction>
#include <QLabel>
#include <QSpacerItem>
#include <QLayout>
#include <QHBoxLayout>
BottomToolBar::BottomToolBar(QWidget *parent) :
    QToolBar(parent)
{

    mSnapShotAction   = new QAction(QIcon(":photo"), "snapshot",this);
    mFullscreenAction = new QAction(QIcon(":expand"),"show fullscreen",this);
    mShowGridAction   = new QAction(QIcon(":grid"),"show Grid",this);
    mZoomComboBox     = new QComboBox;
    mProgressLabel    = new QLabel("34%");
    mAnimLabel        = new QLabel;
    mAnimMovie        = new QMovie;

    mAnimMovie->setFileName(":loading.gif");
    mAnimLabel->setMovie(mAnimMovie);
    mAnimMovie->start();

    QWidget * progressWidget =new QWidget;
    QHBoxLayout * progressLayout = new QHBoxLayout;
    progressWidget->setLayout(progressLayout);
    progressLayout->addWidget(mAnimLabel);
    progressLayout->addWidget(mProgressLabel);
    progressLayout->setContentsMargins(5,0,0,0);
    progressLayout->setSpacing(5);




    addWidget(progressWidget);
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    addWidget(spacerWidget);

    addAction(mSnapShotAction);
    addAction(mFullscreenAction);
    addAction(mShowGridAction);
    addSeparator();
    addWidget(mZoomComboBox);

    mZoomComboBox->addItem("0x");
    mZoomComboBox->addItem("25x");
    mZoomComboBox->addItem("50x");
    mZoomComboBox->addItem("75x");

    layout()->setContentsMargins(0,0,0,0);

    setAllowedAreas(Qt::BottomToolBarArea);
    setFloatable(false);
    setMovable(false);

    setIconSize(QSize(16,16));
    setProgress(0);



}

void BottomToolBar::setEngineView(LifeEngineView *view)
{
    mView = view;
    //  connect(mFullscreenAction,SIGNAL(triggered()),mView->gridWidget(),SLOT(showGrid(bool)));

}

void BottomToolBar::setProgress(int value)
{

    qDebug()<<"PROGRESSS" <<value;

    if (value > 0) {
        mProgressLabel->setText(QString("Loading....%1%").arg(value));
        mAnimMovie->start();
        mAnimLabel->setVisible(true);
        setEnabled(false);

    }

    else
    {
        mProgressLabel->setText("");
        mAnimMovie->stop();
        mAnimLabel->setVisible(false);
        setEnabled(true);
    }


}
