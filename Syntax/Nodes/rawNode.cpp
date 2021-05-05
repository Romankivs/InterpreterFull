#include "../../Visitor.h"

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
    v.visit(*this);;
}

void rawNode::print()
{
    cout << "(Type: raw, Data: ";
    for (const auto& x : get<rawData>(NodeData).rawStr)
        x->print();
    cout << ")";
}