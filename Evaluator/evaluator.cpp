#include "evaluator.h"

evaluator::evaluator(ASTNode* inp, int argc, char** argv, char** envp) :
    inputTree(inp), storage(), argc(argc), argv(argv), envp(envp) {};

void evaluator::visit(argcNode* node) {};

void evaluator::visit(argvNode* node) {};

void evaluator::visit(cmdNode* node)
{
    get<cmdData>(node->NodeData).cmd->accept(*this);
};

void evaluator::visit(echoNode* node) {};

void evaluator::visit(envpNode* node) {};

void evaluator::visit(equalSignNode* node) {};

void evaluator::visit(fullCmdNode* node)
{
    get<fullCmdData>(node->NodeData).command->accept(*this);
};

void evaluator::visit(helpNode* node)
{
    cout << "echo - displays input \n"
        "help - displays information about commands \n"
        "quit - exits prompt \n"
        "argc - displays number of arguments \n"
        "argv - displays arguments \n"
        "envp - displays environmental variables\n"
        "run - run a function from a dll library (usage run \"function\" [\"library\"])\n"
        "Note:library = LibraryFib.dll if not specified\n"
        "name=value - create an environmental variable\n"
        "$var or ${var} - use a variable (use \" \" to escape whitespaces)\n"
        "vars - display variables"
        << endl;
};

void evaluator::visit(quitNode* node)
{
    exit(0);
};

void evaluator::visit(rawNode* node) {};

void evaluator::visit(runNode* node) {};

void evaluator::visit(stringNode* node) {};

void evaluator::visit(varsNode* node) {};

void evaluator::visit(varSubstitutionNode* node) {};
