#ifndef ADDLIFECOMMAND_H
#define ADDLIFECOMMAND_H

#include <QUndoCommand>
#include "simmainwindow.h"
class AddLifeCommand : public QUndoCommand
{
public:
    explicit AddLifeCommand(SimMainWindow * simMain, Life * life);
    void undo();
    void redo();
    
private:
    SimMainWindow * mSimMain;
    Life * mLife;

    
};

#endif // ADDLIFECOMMAND_H
