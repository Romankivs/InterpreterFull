#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(vector<Token>& anInput)
{
    input = anInput;
}

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
    resultRoot->NodeData = fullCmdData{};

    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    if (currentToken.type != Lexema::END_OF_LINE)
        cout << "error: endl not found" << endl;
    return resultRoot;
}

void SyntaxAnalizer::cmd(ASTNode* &node)
{
    node = new cmdNode;
    node->NodeData = cmdData{};
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
        run(get<cmdData>(node->NodeData).cmd);*/
    if (possibleCmds.contains(currentToken.type))
    {
        (*this.*possibleCmds[currentToken.type])(get<cmdData>(node->NodeData).cmd);
    }
    else if (accept(Lexema::NAME))
    {
        equalSign(get<cmdData>(node->NodeData).cmd);
    }
    else
        cout << "syntax error: command not found" << endl;

}

void SyntaxAnalizer::echo(ASTNode* &node) //fix if not enough args
{
    node = new echoNode;
    node->NodeData = echoData{};
    getNext(); // skip "echo"
    if (accept(Lexema::WHITESPACE))
        raw(get<echoData>(node->NodeData).raw);
    else
        cout << "echo: nothing to output" << endl;
}

void SyntaxAnalizer::raw(ASTNode* &node)
{
    node = new rawNode;
    vector<string> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        result.push_back(iter->value);
        getNext();
    }
    for (size_t i = 0 ; i < result.size(); ++i) // for debug
    {
        cout << result[i] << endl;
    }
    node->NodeData = rawData{result};
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
        node = new runNode;
        node->NodeData = runData{(iter - 3)->value, (iter - 1)->value};
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
        node = new equalSignNode;
        node->NodeData = equalSignData{(iter - 3)->value, (iter - 1)->value};
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
