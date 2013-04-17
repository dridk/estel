#include "progressstatusbar.h"
#include <QHBoxLayout>
ProgressStatusBar::ProgressStatusBar(QWidget *parent) :
    QStatusBar(parent)
{

    QWidget * infoWidget = new QWidget;
    infoWidget->setLayout(new QHBoxLayout);


    mGifLabel = new QLabel();
    mGifMovie = new QMovie(":loading.gif");
    mTextLabel  = new QLabel("Loading...");
    mGifLabel->setMovie(mGifMovie);

    infoWidget->layout()->addWidget(mTextLabel);
    infoWidget->layout()->addWidget(mGifLabel);


    addPermanentWidget(infoWidget);
    mGifMovie->start();

    setActive(false);

}

void ProgressStatusBar::setActive(bool active)
{
    mGifLabel->setVisible(active);
    mTextLabel->setVisible(active);
    if (active)
        mGifMovie->start();
    else
        mGifMovie->stop();
}

