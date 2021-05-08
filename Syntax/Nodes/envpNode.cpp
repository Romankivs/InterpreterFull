#include "../../Visitor.h"

void envpNode::accept(Visitor &v)
{
    v.visit(this);;
}
