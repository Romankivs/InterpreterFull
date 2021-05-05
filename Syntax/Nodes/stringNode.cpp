#include "../../Visitor.h"

stringNode::stringNode(const string& inpStr)
{
    NodeData = stringData{inpStr};
}

void stringNode::accept(Visitor &v)
{
    v.visit(*this);;
}

void stringNode::print()
{
    cout << "(Type: string, Data: ";
    cout << get<stringData>(NodeData).value;
    cout << ")";
}
