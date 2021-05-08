#include "../../Visitor.h"

void argcNode::accept(Visitor &v)
{
    v.visit(this);;
}



