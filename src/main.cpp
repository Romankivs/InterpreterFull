#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"
#include "evaluator.h"
#include "Interpreter.h"

int main(int argc, char** argv, char** envp)
{
    /*State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    //Lex analizer//
    LexAnalizer analizer;
    // input
    string inp;
    //getline(cin, inp);
    analizer.setInputString("5=test");
    //Syntax analizer//
    SyntaxAnalizer an(&analizer);
    fullCmdNode* res = dynamic_cast<fullCmdNode*>(an.buildTree());
    an.printTree();
    if (res == nullptr)
        return 1;
    // Evaluator //
    memoryManager strg;
    evaluator eval(res, argc, argv, envp);
    eval.storage = &strg;
    res->accept(eval);
    // second analized str //
    analizer.setInputString(" ecc $5 cum");
    res = dynamic_cast<fullCmdNode*>(an.buildTree());
    if (res == nullptr)
        return 2;
    an.printTree();
    res->accept(eval);*/
    Interpreter interp(argc, argv, envp);
    interp.start();
}

