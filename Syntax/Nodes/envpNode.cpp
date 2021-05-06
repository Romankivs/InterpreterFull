#include "../../Visitor.h"

void envpNode::accept(Visitor &v)
{
    v.visit(this);;
}

void envpNode::print()
{
    cout << "(Type: envp)";
}
