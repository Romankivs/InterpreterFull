#include "../../Visitor/Visitor.h"

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
