#include "SyntaxAnalizer.h"

void SyntaxAnalizer::getNext()
{
    if ((iter + 1) != input->end())
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

shared_ptr<ASTNode> SyntaxAnalizer::buildTree()
{
    iter = input->begin();
    currentToken = *iter;

    resultRoot = make_shared<fullCmdNode>();
    resultRoot->NodeData = fullCmdData{};

    accept(Lexema::WHITESPACE);
    cmd(get<fullCmdData>(resultRoot->NodeData).command);
    expect(Lexema::END_OF_LINE);
    return resultRoot;
}

void SyntaxAnalizer::cmd(shared_ptr<ASTNode> node)
{
    node = make_shared<cmdNode>();
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

void SyntaxAnalizer::echo(shared_ptr<ASTNode> node) //fix if not enough args
{
    node = make_shared<echoNode>();
    node->NodeData = echoData{};
    getNext(); // skip "echo"
    getNext(); // skip ws
    raw(get<echoData>(node->NodeData).raw);
}

void SyntaxAnalizer::raw(shared_ptr<ASTNode> node)
{
    node = make_shared<rawNode>();
    vector<string> result;
    while (currentToken.type != Lexema::END_OF_LINE)
    {
        result.push_back(iter->value);
        getNext();
    }
    for (int i = 0 ; i < result.size(); ++i)
    {
        cout << result[i] << endl;
    }
    node->NodeData = rawData{result};
}

void SyntaxAnalizer::quit(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<quitNode>();
}

void SyntaxAnalizer::argc(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<argcNode>();
}

void SyntaxAnalizer::argv(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<argvNode>();
}

void SyntaxAnalizer::envp(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<envpNode>();
}

void SyntaxAnalizer::help(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<helpNode>();
}

void SyntaxAnalizer::vars(shared_ptr<ASTNode> node)
{
    getNext();
    node = make_shared<varsNode>();
}

void SyntaxAnalizer::run(shared_ptr<ASTNode> node) //fix if not enough args
{
    getNext(); // skip "run"
    getNext(); // skip ws
    cout << (iter-1)->value << endl;
    if ((accept(Lexema::STRING) || accept(Lexema::NAME))
        && (accept(Lexema::WHITESPACE))
        && (accept(Lexema::STRING) || accept(Lexema::NAME)))
    {
        node = make_shared<runNode>((iter - 3)->value, (iter - 1)->value); // fix
    }
    else
        cout << "run: not enough arguments" << endl;

}

void SyntaxAnalizer::equalSign(shared_ptr<ASTNode> node)
{
    node = make_shared<equalSignNode>(iter->value, (iter + 2)->value);
    iter += 3; // walk through name, =, value
}

void SyntaxAnalizer::setInput(vector<Token>& inp)
{
    input = shared_ptr<vector<Token>>(&inp);
}

shared_ptr<ASTNode> SyntaxAnalizer::getResult()
{
    return resultRoot;
}
