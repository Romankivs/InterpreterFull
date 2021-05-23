#include "STNode.h"

void argcNode::accept(Visitor &v)
{
    v.visit(this);;
}

void argvNode::accept(Visitor &v)
{
    v.visit(this);
}

cmdNode::cmdNode()
{
    NodeData = cmdData{};
}

cmdNode::~cmdNode()
{
    delete get<cmdData>(NodeData).cmd;
}

void cmdNode::accept(Visitor &v)
{
    v.visit(this);;
}

echoNode::echoNode()
{
    NodeData = echoData{};
}

echoNode::~echoNode()
{
    delete get<echoData>(NodeData).raw;
}

void echoNode::accept(Visitor &v)
{
    v.visit(this);;
}

void envpNode::accept(Visitor &v)
{
    v.visit(this);;
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

void equalSignNode::accept(Visitor &v)
{
    v.visit(this);;
}

fullCmdNode::fullCmdNode()
{
    NodeData = fullCmdData{};
}

fullCmdNode::~fullCmdNode()
{
    delete get<fullCmdData>(NodeData).command;
}

void fullCmdNode::accept(Visitor &v)
{
    v.visit(this);;
}

void helpNode::accept(Visitor &v)
{
    v.visit(this);;
}

void quitNode::accept(Visitor &v)
{
    v.visit(this);;
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

void rawNode::accept(Visitor &v)
{
    v.visit(this);;
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

void runNode::accept(Visitor &v)
{
    v.visit(this);;
}

stringNode::stringNode(const string& inpStr)
{
    NodeData = stringData{inpStr};
}

void stringNode::accept(Visitor &v)
{
    v.visit(this);;
}


void varsNode::accept(Visitor &v)
{
    v.visit(this);;
}

varSubstitutionNode::varSubstitutionNode()
{
    NodeData = varSubstitutionData{};
}

varSubstitutionNode::varSubstitutionNode(ASTNode* node)
{
    get<varSubstitutionData>(NodeData).variable = node;
}

varSubstitutionNode::~varSubstitutionNode()
{
    delete get<varSubstitutionData>(NodeData).variable;
}

void varSubstitutionNode::accept(Visitor &v)
{
    v.visit(this);;
}




