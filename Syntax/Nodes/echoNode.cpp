#include "../../Visitor.h"

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

void echoNode::print()
{
    cout << "(Type: echo, Data: ";
    get<echoData>(NodeData).raw->print();
    cout << ")";
}
