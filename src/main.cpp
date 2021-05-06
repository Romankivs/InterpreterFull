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
    analizer.setInputString("quit");
    //Syntax analizer//
    SyntaxAnalizer an(&analizer);
    ASTNode* res = an.buildTree();
    an.printTree();
    evaluator eval(res, argc, argv, envp);
    eval.visit(dynamic_cast<fullCmdNode*>(res));
}


