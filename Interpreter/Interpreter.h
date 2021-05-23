#pragma once
#include "evaluator.h"
#include "SyntaxAnalizer.h"
#include "Printer.h"
#include "CmdHistoryManager.h"

class Interpreter
{
public:
    Interpreter(int argc, char** argv, char** envp);
    void start();
private:
    int argc;
    char** argv;
    char** envp;
};

