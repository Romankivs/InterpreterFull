#include "evaluator.h"

evaluator::evaluator(ASTNode* inp, int argc, char** argv, char** envp) :
    inputTree(inp), storage(), argc(argc), argv(argv), envp(envp) {};

evaluator::evaluator(memoryManager* storage, int argc, char** argv, char** envp) :
    storage(storage), argc(argc), argv(argv), envp(envp) {};

string evaluator::evaluate(ASTNode* node)
{
  evaluator v(storage, argc, argv, envp);
  node->accept(v);
  return v.getRes();
}

string evaluator::getRes()
{
    return result;
}

void evaluator::visit(argcNode* node)
{
     result = to_string(argc) + "\n";
};

void evaluator::visit(argvNode* node)
{
    result = "";
    for (int i = 0; i < argc; i++)
        result += string(argv[i]) + "\n";
};

void evaluator::visit(cmdNode* node)
{
    result = evaluate(get<cmdData>(node->NodeData).cmd);
};

void evaluator::visit(echoNode* node)
{
    result = evaluate(get<echoData>(node->NodeData).raw);
};

void evaluator::visit(envpNode* node)
{
    result = "";
    for (int i = 0; envp[i] != nullptr; i++)
    {
        result += string(envp[i]) + "\n";
    }
};

void evaluator::visit(equalSignNode* node)
{
    string name = evaluate(get<equalSignData>(node->NodeData).varName);
    string val = evaluate(get<equalSignData>(node->NodeData).varValue);
    storage->assignValueToVar(name, val);
};

void evaluator::visit(fullCmdNode* node)
{
    cout << evaluate(get<fullCmdData>(node->NodeData).command);
};

void evaluator::visit(helpNode* node)
{
    result = "echo - displays input \n"
        "help - displays information about commands \n"
        "quit - exits prompt \n"
        "argc - displays number of arguments \n"
        "argv - displays arguments \n"
        "envp - displays environmental variables\n"
        "run - run a function from a dll library (usage run \"function\" [\"library\"])\n"
        "Note:library = LibraryFib.dll if not specified\n"
        "name=value - create an environmental variable\n"
        "$var or ${var} - use a variable (use \" \" to escape whitespaces)\n"
        "vars - display variables\n";
};

void evaluator::visit(quitNode* node)
{
    exit(0);
};

void evaluator::visit(rawNode* node)
{
    result = "";
    for (auto x : get<rawData>(node->NodeData).rawStr)
        result += evaluate(x);
};

void evaluator::visit(runNode* node)
{

};

void evaluator::visit(stringNode* node)
{
    result = get<stringData>(node->NodeData).value;
};

void evaluator::visit(varsNode* node)
{
    result = storage->listAllVars();
};

void evaluator::visit(varSubstitutionNode* node)
{
    string varName = get<varSubstitutionData>(node->NodeData).variable;
    result = storage->getVarValue(varName);
};
