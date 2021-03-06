#include "evaluator.h"

evaluator::evaluator(memoryManager* storage, CmdHistoryManager* historyManager, int argc, char** argv, char** envp) :
    storage(storage), historyManager(historyManager), argc(argc), argv(argv), envp(envp) {};

evaluator::~evaluator()
{
    for (auto x : loadedLibs) // closes all loaded libraries
        dlclose(x);
}

string evaluator::evaluate(ASTNode* node)
{
  evaluator v(storage, historyManager, argc, argv, envp);
  node->accept(v);
  return v.getRes();
}

string evaluator::getRes()
{
    return result;
}

void evaluator::warning(const string msg)
{
    cout << "(Warning) " << msg << endl;
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
    result += "\n";
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
        "Note:library = fib.so if not specified\n"
        "name=value - create an environmental variable\n"
        "$var or ${var} - use a variable (use \" \" to escape whitespaces)\n"
        "vars - display variables\n"
        "save - save command history to a file\n"
        "load - load command history from a file\n"
        "purge - delete current command history\n";
};

void evaluator::visit(quitNode* node)
{
    throw (0);
};

void evaluator::visit(rawNode* node)
{
    result = "";
    for (auto x : get<rawData>(node->NodeData).rawStr)
        result += evaluate(x);
};

void evaluator::visit(runNode* node)
{
    const char* lib = evaluate(get<runData>(node->NodeData).lib).c_str();
    string prtlib = string(lib);
    const char* func = evaluate(get<runData>(node->NodeData).func).c_str();
    string prtfunc = string(func);
    void* handle = dlopen(lib, RTLD_LAZY);
    if (handle == nullptr)
    {
        result = "Library \"" + prtlib + "\" not found\n";
        return;
    }
    auto funcP = reinterpret_cast<int (*)()>(dlsym(handle, func));
    if (funcP == nullptr)
    {
        result = "Function \"" + prtfunc + "\" not found\n";
        return;
    }
    result = to_string(funcP()) + "\n";
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
    string varName = evaluate(get<varSubstitutionData>(node->NodeData).variable);
    result = storage->getVarValue(varName);
    if (result.empty())
        warning("evaluator: variable " + varName + " doesn`t exist or empty");
};

void evaluator::visit(saveNode* node)
{
    const string outputFile = evaluate(get<saveData>(node->NodeData).fileName);
    historyManager->saveHistoryToFile(outputFile);
}

void evaluator::visit(loadNode* node)
{
    const string inputFile = evaluate(get<loadData>(node->NodeData).fileName);
    if (!filesystem::exists(inputFile))
    {
        warning("load: such file doesn`t exist");
    }
    else
    {
        historyManager->loadHistoryFromFile(inputFile);
    }
}

void evaluator::visit(purgeNode* node)
{
    historyManager->clearBuffer();
}
