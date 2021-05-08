#include "../../Visitor.h"

equalSignNode::equalSignNode(ASTNode* const varName, ASTNode* const varValue)
{
    NodeData = equalSignData{varName, varValue};
}

equalSignNode::~equalSignNode()
{
    delete get<equalSignData>(NodeData).varName;
    delete get<equalSignData>(NodeData).varValue;
}

void equalSignNode::accept(Visitor &v)
{
    v.visit(this);;
}

