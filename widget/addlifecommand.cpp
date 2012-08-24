#include "addlifecommand.h"


AddLifeCommand::AddLifeCommand(SimMainWindow *simMain, Life *life)
    :QUndoCommand()
{
    mSimMain = simMain;
    mLife = life;
}

void AddLifeCommand::undo()
{
    mSimMain->engine()->remLife(mLife->x(),mLife->y());
    mSimMain->refresh();

}

void AddLifeCommand::redo()
{
    mSimMain->engine()->addLife(mLife);
    mSimMain->refresh();
}
