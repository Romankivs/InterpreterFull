#include "../../Visitor.h"

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
    v.visit(*this);;
}

void fullCmdNode::print()
{
    cout << "ASTree: (Type: fullCmd, Data: ";
    get<fullCmdData>(NodeData).command->print();
    cout << ")" << endl;
}
