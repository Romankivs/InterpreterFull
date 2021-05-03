#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"

int main()
{
    State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    //Lex analizer//
    LexAnalizer analizer;
    analizer.setInputString("run $5 ");
    //Syntax analizer//
    SyntaxAnalizer an(&analizer);
    an.buildTree();
    an.printTree();
}


