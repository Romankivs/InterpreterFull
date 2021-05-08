#include "Interpreter.h"

Interpreter::Interpreter(int argc, char** argv, char** envp) : argc(argc), argv(argv), envp(envp)
{

}

void Interpreter::start()
{
    LexAnalizer analizer;
    SyntaxAnalizer an(&analizer);
    memoryManager strg;
    evaluator eval(&strg, argc, argv, envp);
    fullCmdNode* res;
    string inp;
    try
    {
        while (1)
        {
            cout << "~>";
            getline(cin, inp);
            analizer.setInputString(inp);
            res = dynamic_cast<fullCmdNode*>(an.buildTree());
            //an.printTree();
            res->accept(eval);
            delete res;
        }
    }
    catch (int e)
    {
        cout << "Bye, it was nice working with you!" << endl;
    }
}
