#include "STNode.h"

fullCmdNode::fullCmdNode()
{
    NodeData = fullCmdData{};
}

void fullCmdNode::print()
{
    cout << "ASTree: (Type: fullCmd, Data: ";
    get<fullCmdData>(NodeData).command->print();
    cout << ")" << endl;
}

cmdNode::cmdNode()
{
    NodeData = cmdData{};
}

void cmdNode::print()
{
    cout << "(Type: cmd, Data: ";
    get<cmdData>(NodeData).cmd->print();
    cout << ")";
}

void helpNode::print()
{
    cout << "(Type: help)";
}

void quitNode::print()
{
    cout << "(Type: quit)";
}

void argcNode::print()
{
    cout << "(Type: argc)";
}

void argvNode::print()
{
    cout << "(Type: argv)";
}

echoNode::echoNode()
{
    NodeData = echoData{};
}

void echoNode::print()
{
    cout << "(Type: echo, Data: ";
    get<echoData>(NodeData).raw->print();
    cout << ")";
}

rawNode::rawNode(const vector<string>& inp)
{
    NodeData = rawData{inp};
}

void rawNode::print()
{
    cout << "(Type: raw, Data: ";
    for (const auto& x : get<rawData>(NodeData).rawStr)
        cout << x;
    cout << ")";
}


void envpNode::print()
{
    cout << "(Type: envp)";
}

void varsNode::print()
{
    cout << "(Type: vars)";
}

runNode::runNode(const string& func, const string& lib)
{
    NodeData = runData{lib, func};
}

void runNode::print()
{
    cout << "(Type: run, Data: ";
    cout << get<runData>(NodeData).lib << ", " << get<runData>(NodeData).func;
    cout << ")";
}

equalSignNode::equalSignNode(const string& varName, const string& varValue)
{
    NodeData = equalSignData{varValue, varName};
}

void equalSignNode::print()
{
    cout << "(Type: equalSign, Data: ";
    cout << get<equalSignData>(NodeData).varName << ", " << get<equalSignData>(NodeData).varValue;
    cout << ")";
}
