#include "../../Visitor/Visitor.h"

void envpNode::accept(Visitor &v)
{
    v.visit(this);;
}
