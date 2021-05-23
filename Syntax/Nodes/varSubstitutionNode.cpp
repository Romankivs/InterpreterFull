#include "../../Visitor/Visitor.h"

varSubstitutionNode::varSubstitutionNode()
{
    NodeData = varSubstitutionData{};
}

varSubstitutionNode::varSubstitutionNode(ASTNode* node)
{
    get<varSubstitutionData>(NodeData).variable = node;
}

varSubstitutionNode::~varSubstitutionNode()
{
    delete get<varSubstitutionData>(NodeData).variable;
}

void varSubstitutionNode::accept(Visitor &v)
{
    v.visit(this);;
}
