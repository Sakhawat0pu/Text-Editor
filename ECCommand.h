#ifndef ECC_COMMAND_H
#define ECC_COMMAND_H

#include <vector>
using namespace std;

class ECCommand
{
public:
    virtual ~ECCommand(){}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
};


class ECCommandHistory
{
public:
    ECCommandHistory();
    virtual ~ECCommandHistory();
    bool Undo();
    bool Redo();
    void ExecuteCmd(ECCommand * cmd);
private:
    vector<ECCommand *> listCommands;
    int posCurrCmd;
};

#endif 
