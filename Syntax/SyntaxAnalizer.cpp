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
    fullCmdData tmp;
    resultRoot->NodeData = tmp;

    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    expect(Lexema::END_OF_LINE);
    return resultRoot;
}

void SyntaxAnalizer::cmd(ASTNode* node)
{
    node = new cmdNode;
    cmdData tmp;
    node->NodeData = tmp;
    if (possibleCmds.contains(currentToken.type))
    {
        (*this.*possibleCmds[currentToken.type])(get<cmdData>(node->NodeData).cmd);
        getNext();
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
    echoData tmp;
    node->NodeData = tmp;
    getNext();
    raw(get<echoData>(node->NodeData).raw);
}

void SyntaxAnalizer::raw(ASTNode* node)
{
    node = new rawNode();
    rawData tmp;
    vector<string*> result;
    while (iter->type != Lexema::END_OF_LINE)
    {
        result.push_back(&(iter->value));
        iter += 1;
    }
    tmp.rawStr = result;
    for (int i = 0 ; i < result.size(); ++i)
    {
        cout << *result[i] << endl;
    }
    node->NodeData = tmp;
}

void SyntaxAnalizer::quit(ASTNode* node)
{
    node = new quitNode;
}

void SyntaxAnalizer::argc(ASTNode* node)
{
    node = new argcNode;
}

void SyntaxAnalizer::argv(ASTNode* node)
{
    node = new argvNode;
}

void SyntaxAnalizer::envp(ASTNode* node)
{
    node = new envpNode;
}

void SyntaxAnalizer::help(ASTNode* node)
{
    node = new helpNode;
}

void SyntaxAnalizer::vars(ASTNode* node)
{
    node = new varsNode;
}

void SyntaxAnalizer::run(ASTNode* node) //fix if not enough args
{
    node = new runNode((iter + 1)->value, (iter + 3)->value);
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
