#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"

int main()
{
    State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    LexAnalizer analizer;
    analizer.setInputString("run func lib");
    vector<Token> tokens;
    Token temp;
    while ((temp = analizer.getToken()).value != "")
           tokens.push_back(temp);
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        cout << "Type: " << lexemaToString(tokens[i].type) << " Value: " << tokens[i].value << endl;
    }
    //~~~~~~~~~~~~~~~~~~~//
    SyntaxAnalizer an(tokens);
    an.buildTree();
    ASTNode* res = an.getResult();
    if (res == nullptr)
        cout << "No input" << endl;
    else
        res->print();
}


