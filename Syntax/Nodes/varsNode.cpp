#include "../../Visitor.h"

void varsNode::accept(Visitor &v)
{
    v.visit(*this);;
}

void varsNode::print()
{
    cout << "(Type: vars)";
}
