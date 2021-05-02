#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(const vector<Token>& anInput) :
    input(anInput), resultRoot(nullptr), treeSuccessfulyConstructed(false) {}

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
    if (currentToken.type == type)
    {
        getNext();
        return true;
    }
    return false;
}

void SyntaxAnalizer::error(const string msg)
{
    cout << msg << " (Index: " << (iter - input.begin()) << ")" << endl;
    treeSuccessfulyConstructed = false;
}

ASTNode* SyntaxAnalizer::buildTree()
{
    iter = input.begin();
    currentToken = *iter;
    treeSuccessfulyConstructed = true;
    resultRoot = new fullCmdNode;

    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    if (currentToken.type != Lexema::END_OF_LINE)
        error("fullCmd: endl not found or too many tokens");
    return getResult();
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
        {
            error("cmd: command not found");
        }
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
        error("echo: nothing to output");
}

void SyntaxAnalizer::raw(ASTNode* &node)
{
    vector<string> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        result.push_back(currentToken.value);
        getNext();
    }
    node = new rawNode(result);
}

void SyntaxAnalizer::varSubstitution(ASTNode* &node)
{
    getNext(); // skip "$"
    accept(Lexema::OPEN_BRACE);
    if (accept(Lexema::STRING) || accept(Lexema::NAME))
        node = new varSubstitutionNode(currentToken.value);
    else
        error("varSubstitution: no value to substitute");
    accept(Lexema::CLOSE_BRACE);
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

void SyntaxAnalizer::run(ASTNode* &node)
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
        error("run: not enough or invalid arguments");
}

void SyntaxAnalizer::equalSign(ASTNode* &node)
{
    if (accept(Lexema::EQUAL_SIGN)
        && (accept(Lexema::STRING) || accept(Lexema::NAME))
       )
    {
        node = new equalSignNode((iter - 3)->value, (iter - 1)->value);
    }
    else
        error("equal: wrong token");
}

void SyntaxAnalizer::setInput(const vector<Token>& inp)
{
    input = inp;
}

ASTNode* SyntaxAnalizer::getResult()
{
    if (!treeSuccessfulyConstructed)
        return nullptr;
    return resultRoot;
}

void SyntaxAnalizer::printTree()
{
    if (getResult() == nullptr)
        cout << "printTree: tree wasn`t constructed, printing is not possible" << endl;
    else
        resultRoot->print();
}
