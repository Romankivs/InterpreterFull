#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(vector<Token>& anInput) : input(anInput) {}

SyntaxAnalizer::~SyntaxAnalizer()
{
    delete resultRoot;
}

void SyntaxAnalizer::getNext()
{
    if ((iter + 1) != input.end())
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

bool SyntaxAnalizer::expect(Lexema type) // remove???
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
    iter = input.begin();
    currentToken = *iter;
    resultRoot = new fullCmdNode;
    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    if (currentToken.type != Lexema::END_OF_LINE)
        cout << "error: endl not found or too many arguments" << endl;
    return resultRoot;
}

void SyntaxAnalizer::cmd(ASTNode* &node)
{
    node = new cmdNode;
    switch (currentToken.type)
    {
    case Lexema::ECHO:
        echo(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::QUIT:
        quit(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::ARGC:
        argc(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::ARGV:
        argv(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::ENVP:
        envp(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::HELP:
        help(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::VARS:
        vars(get<cmdData>(node->NodeData).cmd); break;
    case Lexema::RUN:
        run(get<cmdData>(node->NodeData).cmd); break;
    default:
    if (accept(Lexema::NAME))
    {
        equalSign(get<cmdData>(node->NodeData).cmd);
    }
    else
        cout << "syntax error: command not found" << endl;
    }
    /*if (currentToken.type == Lexema::ECHO)  // switch??
        echo(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::QUIT)
        quit(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::ARGC)
        argc(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::ARGV)
        argv(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::ENVP)
        envp(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::HELP)
        help(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::VARS)
        vars(get<cmdData>(node->NodeData).cmd);
    else if (currentToken.type == Lexema::RUN)
        run(get<cmdData>(node->NodeData).cmd);
    if (possibleCmds.contains(currentToken.type))
    {
        (*this.*possibleCmds[currentToken.type])(get<cmdData>(node->NodeData).cmd);
    }
    else if (accept(Lexema::NAME))
    {
        equalSign(get<cmdData>(node->NodeData).cmd);
    }
    else
        cout << "syntax error: command not found" << endl;*/

}

void SyntaxAnalizer::echo(ASTNode* &node) //fix if not enough args
{
    node = new echoNode;
    getNext(); // skip "echo"
    if (accept(Lexema::WHITESPACE))
        raw(get<echoData>(node->NodeData).raw);
    else
        cout << "echo: nothing to output" << endl;
}

void SyntaxAnalizer::raw(ASTNode* &node)
{
    vector<string> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        result.push_back(iter->value);
        getNext();
    }
    node = new rawNode(result);
}

void SyntaxAnalizer::quit(ASTNode* &node)
{
    getNext();
    node = new quitNode;
}

void SyntaxAnalizer::argc(ASTNode* &node)
{
    getNext();
    node = new argcNode;
}

void SyntaxAnalizer::argv(ASTNode* &node)
{
    getNext();
    node = new argvNode;
}

void SyntaxAnalizer::envp(ASTNode* &node)
{
    getNext();
    node = new envpNode;
}

void SyntaxAnalizer::help(ASTNode* &node)
{
    getNext();
    node = new helpNode;
}

void SyntaxAnalizer::vars(ASTNode* &node)
{
    getNext();
    node = new varsNode;
}

void SyntaxAnalizer::run(ASTNode* &node) //fix if not enough args
{
    getNext(); // skip "run"
    if ((accept(Lexema::WHITESPACE))
        && (accept(Lexema::STRING) || accept(Lexema::NAME))
        && (accept(Lexema::WHITESPACE))
        && (accept(Lexema::STRING) || accept(Lexema::NAME)))
    {
        node = new runNode((iter - 3)->value, (iter - 1)->value);
    }
    else
        cout << "run: not enough arguments" << endl;

}

void SyntaxAnalizer::equalSign(ASTNode* &node) // fix me
{
    if (accept(Lexema::EQUAL_SIGN)
        && (accept(Lexema::STRING) || accept(Lexema::NAME))
       )
    {
        node = new equalSignNode((iter - 3)->value, (iter - 1)->value);
    }
    else
        cout << "equal: wrong token" << endl;
}

void SyntaxAnalizer::setInput(vector<Token>& inp)
{
    input = inp;
}

ASTNode* SyntaxAnalizer::getResult()
{
    return resultRoot;
}
