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
    analizer.setInputString("vars");
    //Syntax analizer//
    SyntaxAnalizer an(&analizer);
    fullCmdNode* res = dynamic_cast<fullCmdNode*>(an.buildTree());
    an.printTree();
    if (res == nullptr)
        return 1;
    evaluator eval(res, argc, argv, envp);
    res->accept(eval);
}


