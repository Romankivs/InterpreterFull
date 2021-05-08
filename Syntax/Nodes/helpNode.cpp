#include "../../Visitor.h"

void helpNode::accept(Visitor &v)
{
    v.visit(this);;
}
