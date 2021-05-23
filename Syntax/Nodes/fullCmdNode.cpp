#include "../../Visitor/Visitor.h"

fullCmdNode::fullCmdNode()
{
    NodeData = fullCmdData{};
}

fullCmdNode::~fullCmdNode()
{
    delete get<fullCmdData>(NodeData).command;
}

void fullCmdNode::accept(Visitor &v)
{
    v.visit(this);;
}
