#include "../../Visitor.h"

void helpNode::accept(Visitor &v)
{
    v.visit(this);;
}

void helpNode::print()
{
    cout << "(Type: help)";
}
