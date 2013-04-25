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

#ifndef GRIDVIEWTOOLBAR_H
#define GRIDVIEWTOOLBAR_H

#include <QToolBar>
#include <QComboBox>
#include <QLabel>
#include <QMovie>
#include "lifeengineview.h"
class LifeEngineView;
class BottomToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit BottomToolBar(QWidget *parent = 0);
    void setEngineView(LifeEngineView * view);

public slots:
    void setProgress(int value, const QString& message = QString());


protected slots:
    void onZoomChanged(int index);
    void onShowGridChecked(bool checked);
    void onSnapShotClicked();
    
private:
    QAction * mSnapShotAction ;
    QAction * mFullscreenAction;
    QAction * mShowGridAction;
    QComboBox * mZoomComboBox;
    LifeEngineView * mView;
    QLabel * mProgressLabel;
    QLabel * mAnimLabel;
    QMovie * mAnimMovie;


    
};

#endif // GRIDVIEWTOOLBAR_H
