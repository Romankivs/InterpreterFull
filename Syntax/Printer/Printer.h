#pragma once
#include "../../Visitor/Visitor.h"

class Printer : public Visitor
{
public:
    string print(ASTNode* node);
    string getRes();
    void visit(argcNode* node);
    void visit(argvNode* node);
    void visit(cmdNode* node);
    void visit(echoNode* node);
    void visit(envpNode* node);
    void visit(equalSignNode* node);
    void visit(fullCmdNode* node);
    void visit(helpNode* node);
    void visit(quitNode* node);
    void visit(rawNode* node);
    void visit(runNode* node);
    void visit(stringNode* node);
    void visit(varsNode* node);
    void visit(varSubstitutionNode* node);
    void visit(saveNode* node);
    void visit(loadNode* node);
    void visit(purgeNode* node);
private:
    string result;
};
