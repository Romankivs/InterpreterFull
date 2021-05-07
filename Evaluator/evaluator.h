#pragma once
#include <dlfcn.h>
#include "../Visitor.h"
#include "memoryManager.h"

class evaluator : public Visitor
{
public:
    evaluator(ASTNode* inp, int argc, char** argv, char** envp);
    evaluator(memoryManager* storage, int argc, char** argv, char** envp);
    string evaluate(ASTNode* node);
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
//private:
    ASTNode* inputTree;
    memoryManager* storage;
    int argc;
    string result;
    char** argv;
    char** envp;
};
