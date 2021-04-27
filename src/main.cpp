#include "LexAnalizer.h"
#include "STNode.h"
#include "SyntaxAnalizer.h"

#include <variant>
#include <memory>

struct strVec
{
    int a;
    vector<int> cum;
};

int main()
{
    State stateTmp;
    cout << "Min Levenstein distance between two states: " << stateTmp.minLevensteinDistanceBetweenStates() << endl;
    LexAnalizer analizer;
    analizer.setInputString("   run cum from  " );
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
    shared_ptr<ASTNode> res = an.getResult();
    res->performAction();

    //~~~~~~~~~~~~~~~~~~~~//
    /*variant<int, vector<int>>* inv =  new variant<int, vector<int>>;
    vector<int> tmp;
    *inv = tmp;
    get<vector<int>>(*inv).push_back(9);
    //~~~~~~~~~~~~~~~~~~~~//
    shared_ptr<variant<int, vector<int>>> p(inv);
    get<vector<int>>(*p).push_back(1);
    cout << get<vector<int>>(*inv).front() << endl;*/

}


