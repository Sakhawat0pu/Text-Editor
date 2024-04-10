#include "ECCommand.h"

ECCommandHistory :: ECCommandHistory():posCurrCmd(-1){};
ECCommandHistory :: ~ECCommandHistory()
{
    for(unsigned int i = 0; i<listCommands.size(); i++)
    {
        delete listCommands[i];
    }
    listCommands.clear();
    posCurrCmd = -1;
}
bool ECCommandHistory :: Undo()
{
    if (posCurrCmd < 0)
    {
        return false;
    }
    listCommands[posCurrCmd]->UnExecute();
    --posCurrCmd;
    return true;
}

bool ECCommandHistory :: Redo()
{
    if (posCurrCmd < 0)
    {
        return false;
    }
    ++posCurrCmd;
    listCommands[posCurrCmd]->Execute();
    return true;
}

void ECCommandHistory :: ExecuteCmd(ECCommand *cmd)
{
    cmd->Execute();
    if (posCurrCmd >= -1)
    {
        for (unsigned int i = posCurrCmd+1; i<listCommands.size(); i++)
        {
            delete listCommands.back();
            listCommands.pop_back();
        }
        listCommands.push_back(cmd);
        ++posCurrCmd;
    }
}
