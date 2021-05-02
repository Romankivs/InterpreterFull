#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"

int main()
{
    State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    //Lex analizer//
    LexAnalizer analizer;
    analizer.setInputString(" r=function");
    vector<Token> tokens;
    Token temp;
    while ((temp = analizer.getToken()).value != "")
           tokens.push_back(temp);
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        cout << "Type: " << lexemaToString(tokens[i].type) << " Value: " << tokens[i].value << endl;
    }
    //Syntax analizer//
    SyntaxAnalizer an(tokens);
    an.buildTree();
    an.printTree();
}


