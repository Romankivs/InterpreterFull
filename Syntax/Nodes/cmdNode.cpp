#include "../../Visitor/Visitor.h"

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

