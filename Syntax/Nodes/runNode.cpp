#include "STNode.h"

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
