#include "../../Visitor.h"

void argvNode::accept(Visitor &v)
{
    v.visit(*this);
}

void argvNode::print()
{
    cout << "(Type: argv)";
}
