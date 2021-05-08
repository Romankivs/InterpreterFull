#include "../../Visitor.h"

varSubstitutionNode::varSubstitutionNode()
{
    NodeData = varSubstitutionData{};
}

varSubstitutionNode::varSubstitutionNode(const string& varName)
{
    NodeData = varSubstitutionData{varName};
}

void varSubstitutionNode::accept(Visitor &v)
{
    v.visit(this);;
}
