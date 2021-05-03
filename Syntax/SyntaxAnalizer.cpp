#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(LexAnalizer* const inpLex) :
    inputSrc(inpLex), resultRoot(nullptr), treeSuccessfulyConstructed(false) {}

SyntaxAnalizer::~SyntaxAnalizer()
{
    delete resultRoot;
}

void SyntaxAnalizer::getNext()
{
    currentToken = inputSrc->getToken();
    cout << "Type: " << lexemaToString(currentToken.type) << " Value: " << currentToken.value << endl;
    ++index;
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

bool SyntaxAnalizer::curTokEqual(Lexema type)
{
    return (currentToken.type == type);
}

void SyntaxAnalizer::error(const string msg)
{
    cout << msg << " (Index: " << index << ")" << endl;
    treeSuccessfulyConstructed = false;
}

ASTNode* SyntaxAnalizer::buildTree()
{
    index = 0;
    getNext();
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
    case Lexema::NAME:
        equalSign(get<cmdData>(node->NodeData).cmd); break;
    default:
        error("cmd: command not found");
    }
}

void SyntaxAnalizer::varSubstitution(ASTNode* &node)
{
    accept(Lexema::OPEN_BRACE);
    if (curTokEqual(Lexema::STRING) || curTokEqual(Lexema::NAME))
    {
        node = new varSubstitutionNode(currentToken.value);
        getNext();
    }
    else
        error("varSubstitution: no value to substitute");
    accept(Lexema::CLOSE_BRACE);
}


void SyntaxAnalizer::run(ASTNode* &node)
{
    getNext(); // skip "run"
    bool success = accept(Lexema::WHITESPACE);
    node = new runNode();
    if (curTokEqual(Lexema::STRING) || curTokEqual(Lexema::NAME))
    {
        get<runData>(node->NodeData).func = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
        varSubstitution(get<runData>(node->NodeData).func);
    else
        success = false;
    success = accept(Lexema::WHITESPACE);
    if (curTokEqual(Lexema::STRING) || curTokEqual(Lexema::NAME))
    {
        get<runData>(node->NodeData).lib = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
        varSubstitution(get<runData>(node->NodeData).lib);
    else
        success = false;
    if (!success)
        error("run: not enough or invalid arguments");
}

void SyntaxAnalizer::equalSign(ASTNode* &node)
{
    node = new equalSignNode(new stringNode(currentToken.value), nullptr);
    getNext();
    if (!accept(Lexema::EQUAL_SIGN))
        error("cmd: command not found");
    if (curTokEqual(Lexema::STRING) || curTokEqual(Lexema::NAME))
    {
        get<equalSignData>(node->NodeData).varValue = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
    {
        varSubstitution(get<equalSignData>(node->NodeData).varValue);
    }
    else
        error("equal: wrong token");
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
    vector<ASTNode*> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        if (accept(Lexema::DOLLAR_SIGN))
        {
            ASTNode* res;
            varSubstitution(res);
            result.push_back(res);
        }
        else
        {
            result.push_back(new stringNode(currentToken.value));
            getNext();
        }
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



