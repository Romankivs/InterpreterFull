#include "SyntaxAnalizer.h"

void SyntaxAnalizer::getNext()
{
    iter +=1;
    currentToken = *iter;
}

bool SyntaxAnalizer::accept(Lexema type)
{
    cout << currentToken.type << ":" << type << endl;
    if (currentToken.type == type)
    {
        getNext();
        return true;
    }
    return false;
}

bool SyntaxAnalizer::expect(Lexema type)
{
    if (accept(type))
    {
        return true;
    }
    cout << "unexpected token" << endl;
    return false;
}

ASTNode* SyntaxAnalizer::buildTree()
{
    iter = input->begin();
    currentToken = *iter;

    resultRoot = new fullCmdNode;
    resultRoot->NodeData = fullCmdData{};

    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    expect(Lexema::END_OF_LINE);
    return resultRoot;
}

void SyntaxAnalizer::cmd(ASTNode* node)
{
    node = new cmdNode;
    node->NodeData = cmdData{};
    if (possibleCmds.contains(currentToken.type))
    {
        (*this.*possibleCmds[currentToken.type])(get<cmdData>(node->NodeData).cmd);
    }
    else if (accept(Lexema::STRING) || accept(Lexema::NAME))
    {
        equalSign(get<cmdData>(node->NodeData).cmd);
    }
    else
        cout << " syntax error: command not found" << endl;
}

void SyntaxAnalizer::echo(ASTNode* node) //fix if not enough args
{
    node = new echoNode;
    node->NodeData = echoData{};
    getNext(); // skip "echo"
    getNext(); // skip ws
    raw(get<echoData>(node->NodeData).raw);
}

void SyntaxAnalizer::raw(ASTNode* node)
{
    node = new rawNode();
    vector<string*> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        result.push_back(&(iter->value));
        getNext();
    }
    for (int i = 0 ; i < result.size(); ++i)
    {
        cout << *result[i] << endl;
    }
    node->NodeData = rawData{result};
}

void SyntaxAnalizer::quit(ASTNode* node)
{
    getNext();
    node = new quitNode;
}

void SyntaxAnalizer::argc(ASTNode* node)
{
    getNext();
    node = new argcNode;
}

void SyntaxAnalizer::argv(ASTNode* node)
{
    getNext();
    node = new argvNode;
}

void SyntaxAnalizer::envp(ASTNode* node)
{
    getNext();
    node = new envpNode;
}

void SyntaxAnalizer::help(ASTNode* node)
{
    getNext();
    node = new helpNode;
}

void SyntaxAnalizer::vars(ASTNode* node)
{
    getNext();
    node = new varsNode;
}

void SyntaxAnalizer::run(ASTNode* node) //fix if not enough args
{
    getNext(); // skip "run"
    getNext(); // skip ws
    cout << (iter-1)->value << endl;
    if ((accept(Lexema::STRING) || accept(Lexema::NAME))
        && (accept(Lexema::WHITESPACE))
        && (accept(Lexema::STRING) || accept(Lexema::NAME)))
    {
        node = new runNode((iter - 3)->value, (iter - 1)->value); // fix
    }
    else
        cout << "run: not enough arguments" << endl;

}

void SyntaxAnalizer::equalSign(ASTNode* node)
{
    node = new equalSignNode(iter->value, (iter + 2)->value);
    iter += 3; // walk through name, =, value
}

void SyntaxAnalizer::setInput(vector<Token>& inp)
{
    input = &inp;
}

ASTNode* SyntaxAnalizer::getResult()
{
    return resultRoot;
}
