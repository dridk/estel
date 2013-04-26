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
#include <QFileDialog>
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
    mPerfIcon         = new QLabel;
    mPerfLabel        = new QLabel;

    mPerfIcon->setPixmap(QIcon(":speed").pixmap(16,16));
    mShowGridAction->setCheckable(true);
    mShowGridAction->setChecked(true);
    mAnimMovie->setFileName(":loading.gif");
    mAnimLabel->setMovie(mAnimMovie);
    mAnimMovie->start();

    QWidget * progressWidget =new QWidget;
    QHBoxLayout * progressLayout = new QHBoxLayout;
    progressWidget->setLayout(progressLayout);
    progressLayout->addWidget(mAnimLabel);
    progressLayout->addWidget(mProgressLabel);
    progressLayout->addWidget(mPerfIcon);
    progressLayout->addWidget(mPerfLabel);

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

    mZoomComboBox->addItem(QIcon(":zoom"),"1x",1);
    mZoomComboBox->addItem(QIcon(":zoom"),"2x",2);
    mZoomComboBox->addItem(QIcon(":zoom"),"3x",3);
    mZoomComboBox->addItem(QIcon(":zoom"),"4x",4);
    mZoomComboBox->setFrame(false);

    mZoomComboBox->setIconSize(QSize(16,16));

    layout()->setContentsMargins(0,0,0,0);

    setAllowedAreas(Qt::BottomToolBarArea);
    setFloatable(false);
    setMovable(false);

    setIconSize(QSize(16,16));
    setProgress(0);

    connect(mZoomComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onZoomChanged(int)));
    connect(mShowGridAction,SIGNAL(triggered(bool)),this,SLOT(onShowGridChecked(bool)));
    connect(mSnapShotAction,SIGNAL(triggered()),this,SLOT(onSnapShotClicked()));


}

void BottomToolBar::setEngineView(LifeEngineView *view)
{
    mView = view;


}

void BottomToolBar::setProgress(int value, const QString &message)
{
    if (value == 1)
    mTime.start();

    if (value == 0) {

        mPerfLabel->setText(QString("%1 ms").arg(mTime.elapsed()));

    }

    if (value > 0) {
        mProgressLabel->setText(QString(message+"...%1%").arg(value));
        mAnimMovie->start();
        mAnimLabel->setVisible(true);
        mPerfIcon->setVisible(false);
        mPerfLabel->setVisible(false);
        setEnabled(false);
    }

    else
    {
        mProgressLabel->setText("");
        mAnimMovie->stop();
        mAnimLabel->setVisible(false);
        mPerfIcon->setVisible(true);
        mPerfLabel->setVisible(true);
        setEnabled(true);


    }


}

void BottomToolBar::onZoomChanged(int index)
{
    if (mView == NULL)
        return;


    mView->gridWidget()->setZoom(mZoomComboBox->itemData(index).toInt());



}

void BottomToolBar::onShowGridChecked(bool checked)
{
    if (mView == NULL)
        return;
    mView->gridWidget()->showGrid(checked);


}

void BottomToolBar::onSnapShotClicked()
{

    QString filename = QFileDialog::getSaveFileName();

    mView->gridWidget()->showGrid(false);
    mView->gridWidget()->snap()->save(filename);
    mView->gridWidget()->showGrid(true);


}
