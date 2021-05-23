#include "../../Visitor/Visitor.h"

void varsNode::accept(Visitor &v)
{
    v.visit(this);;
}
