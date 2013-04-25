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

#ifndef GENEDIALOG_H
#define GENEDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QDialogButtonBox>
#include "gene.h"
#include "colorgradientwidget.h"
#include "colorbutton.h"
class GeneDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GeneDialog(QWidget *parent = 0);
    ~GeneDialog();
    void setGene(const Gene& gene);
    Gene gene() const;


protected slots:
    void nameChanged(const QString& name);

private:
    Gene mGene;
    QLineEdit * mNameEdit;
    QSpinBox * mValueSpinBox;

    QSpinBox * mVarSpinBox;
    QDoubleSpinBox * mProbSpinBox;
    QDialogButtonBox * mButtonBox;
    ColorGradientWidget * mColorWidget;
    ColorButton * mColorButton;




    
};

#endif // GENEDIALOG_H
