#include "Printer.h"

#include "evaluator.h"

string Printer::print(ASTNode* node)
{
  Printer v;
  node->accept(v);
  return v.getRes();
}

string Printer::getRes()
{
    return result;
}

void Printer::visit(argcNode* node)
{
     result = "(Type: argc)";
};

void Printer::visit(argvNode* node)
{
    result = "(Type: argv)";
};

void Printer::visit(cmdNode* node)
{
    result = "(Type: cmd, Data: " + print(get<cmdData>(node->NodeData).cmd) + ")";
};

void Printer::visit(echoNode* node)
{
    result = "(Type: echo, Data: " + print(get<echoData>(node->NodeData).raw) + ")";
};

void Printer::visit(envpNode* node)
{
    result = "(Type: envp)";
};

void Printer::visit(equalSignNode* node)
{
    result = "(Type: equalSign, Data: ";
    result += print(get<equalSignData>(node->NodeData).varName);
    result += ", ";
    result += print(get<equalSignData>(node->NodeData).varValue);
    result += ")";
};

void Printer::visit(fullCmdNode* node)
{
    cout << "ASTree: (Type: fullCmd, Data: ";
    cout << print(get<fullCmdData>(node->NodeData).command);
    cout << ")" << endl;
};

void Printer::visit(helpNode* node)
{
    result = "(Type: help)";
};

void Printer::visit(quitNode* node)
{
    result = "(Type: quit)";
};

void Printer::visit(rawNode* node)
{
    result = "(Type: raw, Data: ";
    for (const auto& x : get<rawData>(node->NodeData).rawStr)
        result += print(x);
    result += ")";
};

void Printer::visit(runNode* node)
{
    result += "(Type: run, Data: ";
    result += print(get<runData>(node->NodeData).func);
    result += ", ";
    result += print(get<runData>(node->NodeData).lib);
    result += ")";
};

void Printer::visit(stringNode* node)
{
    result = "(Type: string, Data: " + get<stringData>(node->NodeData).value + ")";
};

void Printer::visit(varsNode* node)
{
    result = "(Type: vars)";
};

void Printer::visit(varSubstitutionNode* node)
{
    result =  "(Type: varSubstitution, Data: " + print(get<varSubstitutionData>(node->NodeData).variable) + ")";
};

void Printer::visit(saveNode* node)
{
    result = "(Type: save)";
}

void Printer::visit(loadNode* node)
{
    result = "(Type: load)";
}

void Printer::visit(purgeNode* node)
{
    result = "(Type: purge)";
}
