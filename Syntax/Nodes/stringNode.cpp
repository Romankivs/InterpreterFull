#include "STNode.h"

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
