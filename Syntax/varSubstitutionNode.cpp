#include "STNode.h"

varSubstitutionNode::varSubstitutionNode()
{
    NodeData = varSubstitutionData{};
}

varSubstitutionNode::varSubstitutionNode(const string& varName)
{
    NodeData = varSubstitutionData{varName};
}

void varSubstitutionNode::print()
{
    cout << "(Type: varSubstitution, Data: ";
    cout << get<varSubstitutionData>(NodeData).variable;
    cout << ")";
}
