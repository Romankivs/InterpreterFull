#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"
#include "evaluator.h"

int main(int argc, char** argv, char** envp)
{
    State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    //Lex analizer//
    LexAnalizer analizer;
    analizer.setInputString("4=cannot");
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
    analizer.setInputString("run $4 ${4}");
    res = dynamic_cast<fullCmdNode*>(an.buildTree());
    an.printTree();
    res->accept(eval);
}


