#include "../../Visitor.h"

void quitNode::accept(Visitor &v)
{
    v.visit(this);;
}

void quitNode::print()
{
    cout << "(Type: quit)";
}
