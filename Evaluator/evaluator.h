#pragma once
#include <dlfcn.h>
#include <filesystem>
#include "../Visitor/Visitor.h"
#include "memoryManager.h"
#include "CmdHistoryManager.h"

class evaluator : public Visitor
{
public:
    evaluator(memoryManager* storage, CmdHistoryManager* historyManager, int argc, char** argv, char** envp);
    ~evaluator();
    string evaluate(ASTNode* node);
    string getRes();
    void warning(const string msg);
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
    ASTNode* inputTree;
    memoryManager* storage;
    CmdHistoryManager* historyManager;
    vector<void*> loadedLibs;
    string result;
    int argc;
    char** argv;
    char** envp;
};
