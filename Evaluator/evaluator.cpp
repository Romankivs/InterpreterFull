#include "evaluator.h"

evaluator::evaluator(ASTNode* inp, int argc, char** argv, char** envp) :
    inputTree(inp), storage(), argc(argc), argv(argv), envp(envp) {};

void evaluator::visit(argcNode* node)
{
     cout << "Number of arguments: " << argc << endl;
};

void evaluator::visit(argvNode* node)
{
    for (int i = 0; i < argc; i++)
        cout << argv[i] << endl;
};

void evaluator::visit(cmdNode* node)
{
    get<cmdData>(node->NodeData).cmd->accept(*this);
};

void evaluator::visit(echoNode* node) {};

void evaluator::visit(envpNode* node)
{
    for (int i = 0; envp[i] != nullptr; i++)
        cout << envp[i] << endl;
};

void evaluator::visit(equalSignNode* node)
{
    //string name = get<equalSignData>(node->NodeData).varName;
    //string val = get<equalSignData>(node->NodeData).varValue;
};

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
    cout << "Bye, it was nice working with you!" << endl;
    exit(0);
};

void evaluator::visit(rawNode* node) {};

void evaluator::visit(runNode* node) {};

void evaluator::visit(stringNode* node) {};

void evaluator::visit(varsNode* node)
{
    cout << storage.listAllVars();
};

void evaluator::visit(varSubstitutionNode* node) {};
