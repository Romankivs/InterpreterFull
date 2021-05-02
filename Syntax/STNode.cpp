#include "STNode.h"

fullCmdNode::fullCmdNode()
{
    NodeData = fullCmdData{};
}

fullCmdNode::~fullCmdNode()
{
    delete get<fullCmdData>(NodeData).command;
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

cmdNode::~cmdNode()
{
    delete get<cmdData>(NodeData).cmd;
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

echoNode::~echoNode()
{
    delete get<echoData>(NodeData).raw;
}

void echoNode::print()
{
    cout << "(Type: echo, Data: ";
    get<echoData>(NodeData).raw->print();
    cout << ")";
}

rawNode::rawNode(const vector<ASTNode*> inp)
{
    NodeData = rawData{inp};
}

rawNode::~rawNode()
{
    for (auto x : get<rawData>(NodeData).rawStr)
        delete x;
}

void rawNode::print()
{
    cout << "(Type: raw, Data: ";
    for (const auto& x : get<rawData>(NodeData).rawStr)
        x->print();
    cout << ")";
}

varSubstitutionNode::varSubstitutionNode()
{
    NodeData = varSubstitutionData{};
}

varSubstitutionNode::varSubstitutionNode(const string& varName)
{
    NodeData = varSubstitutionData{varName};
}

void varSubstitutionNode::print()
{
    cout << "(Type: varSubstitution, Data: ";
    cout << get<varSubstitutionData>(NodeData).variable;
    cout << ")";
}

stringNode::stringNode(const string& inpStr)
{
    NodeData = stringData{inpStr};
}

void stringNode::print()
{
    cout << "(Type: string, Data: ";
    cout << get<stringData>(NodeData).value;
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

runNode::runNode()
{
    NodeData = runData{};
}

runNode::runNode(ASTNode* const func, ASTNode* const lib)
{
    NodeData = runData{lib, func};
}

runNode::~runNode()
{
    delete get<runData>(NodeData).func; delete get<runData>(NodeData).lib;
}
void runNode::print()
{
    cout << "(Type: run, Data: ";
    get<runData>(NodeData).func->print();
    cout << ", ";
    get<runData>(NodeData).lib->print();
    cout << ")";
}

equalSignNode::equalSignNode(ASTNode* const varName, ASTNode* const varValue)
{
    NodeData = equalSignData{varName, varValue};
}

equalSignNode::~equalSignNode()
{
    delete get<equalSignData>(NodeData).varName;
    delete get<equalSignData>(NodeData).varValue;
}

void equalSignNode::print()
{
    cout << "(Type: equalSign, Data: ";
    get<equalSignData>(NodeData).varName->print();
    cout << ", ";
    get<equalSignData>(NodeData).varValue->print();
    cout << ")";
}
