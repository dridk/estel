#ifndef PROGRESSSTATUSBAR_H
#define PROGRESSSTATUSBAR_H

#include <QStatusBar>
#include <QLabel>
#include <QMovie>
class ProgressStatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit ProgressStatusBar(QWidget *parent = 0);
public slots:
    void setActive(bool active);

private:
    QLabel * mGifLabel;
    QLabel * mTextLabel;
    QMovie * mGifMovie;

    
};

#endif // PROGRESSSTATUSBAR_H
