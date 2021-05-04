#include "STNode.h"

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
