#include "STNode.h"

void fullCmdNode::evaluate()
{
    cout << "ASTree: (Type: fullCmd, Data: ";
    get<fullCmdData>(NodeData).command->evaluate();
    cout << ")" << endl;
}

void cmdNode::evaluate()
{
    cout << "(Type: cmd, Data: ";
    get<cmdData>(NodeData).cmd->evaluate();
    cout << ")";
}

void helpNode::evaluate()
{
    cout << "(Type: help)";
}

void quitNode::evaluate()
{
    cout << "(Type: quit)";
}

void argcNode::evaluate()
{
    cout << "(Type: argc)";
}

void argvNode::evaluate()
{
    cout << "(Type: argv)";
}

void echoNode::evaluate()
{
    cout << "(Type: echo, Data: ";
    get<echoData>(NodeData).raw->evaluate();
    cout << ")";
}

void rawNode::evaluate()
{
    cout << "(Type: raw, Data: ";
    for (const auto& x : get<rawData>(NodeData).rawStr)
        cout << x;
    cout << ")";
}


void envpNode::evaluate()
{
    cout << "(Type: envp)";
}

void varsNode::evaluate()
{
    cout << "(Type: vars)";
}

void runNode::evaluate()
{
    cout << "(Type: run, Data: ";
    cout << get<runData>(NodeData).lib << ", " << get<runData>(NodeData).func;
    cout << ")";
}

void equalSignNode::evaluate()
{
    cout << "(Type: equalSign, Data: ";
    cout << get<equalSignData>(NodeData).varName << ", " << get<equalSignData>(NodeData).varValue;
    cout << ")";
}
