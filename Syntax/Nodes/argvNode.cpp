#include "../../Visitor/Visitor.h"

void argvNode::accept(Visitor &v)
{
    v.visit(this);
}
