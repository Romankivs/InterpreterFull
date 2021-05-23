#include "../../Visitor/Visitor.h"

void quitNode::accept(Visitor &v)
{
    v.visit(this);;
}

