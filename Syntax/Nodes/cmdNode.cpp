#include "../../Visitor.h"

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
    v.visit(*this);;
}

void cmdNode::print()
{
    cout << "(Type: cmd, Data: ";
    get<cmdData>(NodeData).cmd->print();
    cout << ")";
}
