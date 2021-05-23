#include "Interpreter.h"

Interpreter::Interpreter(int argc, char** argv, char** envp) : argc(argc), argv(argv), envp(envp) {};

void Interpreter::start()
{
    LexAnalizer analizer;
    SyntaxAnalizer an(&analizer);
    memoryManager storage;
    CmdHistoryManager historyManager;
    evaluator eval(&storage, &historyManager, argc, argv, envp);
    ASTNode* res;
    string inp;
    #ifdef DEBUG
        Printer printer;
    #endif // DEBUG
    try
    {
        while (1)
        {
            cout << "~>";
            getline(cin, inp);
            if (!inp.empty())
            {
                historyManager.addToBuffer(inp + "\n");
                analizer.setInputString(inp);
                res = an.buildTree();
                #ifdef DEBUG
                    printer.print(res);
                #endif // DEBUG
                res->accept(eval);
                delete res;
            }
        }
    }
    catch (int e)
    {
        cout << "Bye, it was nice working with you!" << endl;
    }
}
