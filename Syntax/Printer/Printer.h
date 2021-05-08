#pragma once
#include "../../Visitor.h"

class Printer : public Visitor
{
public:
    string print(ASTNode* node);
    string getRes();
    virtual void visit(argcNode* node);
    virtual void visit(argvNode* node);
    virtual void visit(cmdNode* node);
    virtual void visit(echoNode* node);
    virtual void visit(envpNode* node);
    virtual void visit(equalSignNode* node);
    virtual void visit(fullCmdNode* node);
    virtual void visit(helpNode* node);
    virtual void visit(quitNode* node);
    virtual void visit(rawNode* node);
    virtual void visit(runNode* node);
    virtual void visit(stringNode* node);
    virtual void visit(varsNode* node);
    virtual void visit(varSubstitutionNode* node);
private:
    string result;
};
