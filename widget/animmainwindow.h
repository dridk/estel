#ifndef ANIMMAINWINDOW_H
#define ANIMMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AnimMainWindow;
}

class AnimMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AnimMainWindow(QWidget *parent = 0);
    ~AnimMainWindow();
    
private:
    Ui::AnimMainWindow *ui;
};

#endif // ANIMMAINWINDOW_H
