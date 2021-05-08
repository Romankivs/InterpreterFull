#include "SyntaxAnalizer.h"

SyntaxAnalizer::SyntaxAnalizer(LexAnalizer* const inpLex) :
    inputSrc(inpLex), resultRoot(nullptr), treeSuccessfulyConstructed(false) {}

SyntaxAnalizer::~SyntaxAnalizer()
{
    delete resultRoot;
}

void SyntaxAnalizer::getNext()
{
    if ( index != inputTokens.size())
    {
        ++index;
        currentToken = inputTokens[index - 1];
    }
    else
    {
        currentToken = inputSrc->getToken();
        inputTokens.push_back(currentToken);
        cout << "Type: " << lexemaToString(currentToken.type) << " Value: " << currentToken.value << endl;
        ++index;
    }
}

void SyntaxAnalizer::unGet()
{
    --index;
    currentToken = inputTokens[index - 1];
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

void SyntaxAnalizer::warning(const string msg)
{
    cout << "(Warning) " << msg << " (Index: " << index << ")" << endl;
}

ASTNode* SyntaxAnalizer::buildTree()
{
    index = 0;
    inputTokens.clear();
    getNext();
    treeSuccessfulyConstructed = true;

    resultRoot = new fullCmdNode;
    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    if (currentToken.type != Lexema::END_OF_LINE)
        warning("fullCmd: too many tokens, some of them were ignored");
    return getResult();
}

Token SyntaxAnalizer::searchForRightFunc(const string& inp)
{
    Token bestSuitedFunc;
    int minDist = INT_MAX;
    for (auto& x : posCmds)
    {
        int dist = LevensteinDistance(inp, x.first);
        if (dist < minDist)
        {
            minDist = dist;
            bestSuitedFunc = Token{x.second, x.first};
        }
    }
    if (minDist > 2) // if no suitable replacement found
        return Token{Lexema::STRING, inp};
    return bestSuitedFunc;
}

void SyntaxAnalizer::cmd(ASTNode* &node)
{
    node = new cmdNode;
    /*bool validCmd = false;
    for (int i = 0; i < posCmds.size(); ++i)
        if currentToken.type
    */
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
    case Lexema::STRING:
        equalSign(get<cmdData>(node->NodeData).cmd); break;
    default:
        warning("cmd: wrong token will be replaced with echo");
        echo(get<cmdData>(node->NodeData).cmd);
    }
}

void SyntaxAnalizer::run(ASTNode* &node)
{
    getNext(); // skip "run"
    accept(Lexema::WHITESPACE);
    node = new runNode();
    if (curTokEqual(Lexema::STRING))
    {
        get<runData>(node->NodeData).func = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
        varSubstitution(get<runData>(node->NodeData).func);
    else
    {
        warning("run: invalid function replaced with random");
        currentToken = Token{Lexema::STRING, "random"};
        get<runData>(node->NodeData).func = new stringNode(currentToken.value);
        getNext();
    }
    accept(Lexema::WHITESPACE);
    if (curTokEqual(Lexema::STRING))
    {
        get<runData>(node->NodeData).lib = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
        varSubstitution(get<runData>(node->NodeData).lib);
    else
    {
        warning("run: invalid lib replaced with LibraryFib.so");
        currentToken = Token{Lexema::STRING, "LibraryFib.so"};
        get<runData>(node->NodeData).lib = new stringNode(currentToken.value);
        getNext();
    }
}

void SyntaxAnalizer::equalSign(ASTNode* &node)
{
    node = new equalSignNode(new stringNode(currentToken.value), nullptr);
    getNext();
    if (!accept(Lexema::EQUAL_SIGN))
        error("cmd: command not found");
    if (curTokEqual(Lexema::STRING))
    {
        get<equalSignData>(node->NodeData).varValue = new stringNode(currentToken.value);
        getNext();
    }
    else if (accept(Lexema::DOLLAR_SIGN))
    {
        varSubstitution(get<equalSignData>(node->NodeData).varValue);
    }
    else
    {
        warning("equal: wrong token, it was substituted with empty string");
        currentToken = Token{Lexema::STRING, ""};
        get<equalSignData>(node->NodeData).varValue = new stringNode(currentToken.value);
        getNext();
    }
}

void SyntaxAnalizer::echo(ASTNode* &node)
{
    node = new echoNode;
    getNext(); // skip "echo"
    if (accept(Lexema::WHITESPACE))
        raw(get<echoData>(node->NodeData).raw);
    else
    {
        warning("echo: nothing to output");
        raw(get<echoData>(node->NodeData).raw);
    }
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
    if (result.empty()) // output nothing
        result.push_back(new stringNode(""));
    node = new rawNode(result);
}

void SyntaxAnalizer::varSubstitution(ASTNode* &node)
{
    accept(Lexema::OPEN_BRACE);
    if (curTokEqual(Lexema::STRING))
    {
        node = new varSubstitutionNode(currentToken.value);
        getNext();
    }
    else
    {
        warning("varSubstitution: no value to substitute, replaced with whitespace");
        currentToken = Token{Lexema::STRING, " "};
        node = new varSubstitutionNode(currentToken.value);
        getNext();
    }
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



