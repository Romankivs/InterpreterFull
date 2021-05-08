#include "../../Visitor.h"

void quitNode::accept(Visitor &v)
{
    v.visit(this);;
}

