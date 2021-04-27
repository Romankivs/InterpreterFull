#pragma once
#include <vector>
#include <iostream>
#include <variant>
#include <memory>

using namespace std;

class ASTNode;
class cmdNode;
class rawNode;

struct fullCmdData
{
    cmdNode* command;
};

struct equalSignData
{
    string* varName, *varValue;
};

struct cmdData
{
    ASTNode* cmd;
};

struct echoData
{
    rawNode* raw;
};

struct rawData
{
    vector<string*> rawStr;
};

class ASTNode
{
public:
    virtual void performAction() {}; //reserved for later usage
    variant<fullCmdData, equalSignData, cmdData, echoData, rawData> NodeData;
};

class openBraceNode : public ASTNode
{
public:
    openBraceNode();
private:
};

class closeBraceNode : public ASTNode
{
public:
    closeBraceNode();
private:
};

class dollarSignNode : public ASTNode
{
public:
    dollarSignNode();
private:

};

class equalSignNode : public ASTNode
{
public:
    equalSignNode(string& name, string& value);
    void performAction() override;
};

class nameNode : public ASTNode
{
public:
    nameNode();
private:

};

class cmdNode : public ASTNode
{
public:
    cmdNode();
    void performAction() override;
};

class fullCmdNode : public ASTNode
{
public:
    fullCmdNode();
    void performAction() override;
};

class rawNode : public ASTNode
{
public:
    rawNode() {};
    void performAction() override {}
};

class echoNode : public ASTNode
{
public:
    echoNode() {};
    void performAction() override {};
};

class argcNode : public ASTNode
{
public:
    argcNode() {};
    void performAction() override {};
};

class argvNode : public ASTNode
{
public:
    argvNode() {};
    void performAction() override {};
};

class envpNode : public ASTNode
{
public:
    envpNode() {};
    void performAction() override {};
};

class quitNode : public ASTNode
{
public:
    quitNode() {};
    void performAction() override {};
};

class helpNode : public ASTNode
{
public:
    helpNode() {};
    void performAction() override {};
};

class varsNode : public ASTNode
{
public:
    varsNode() {};
    void performAction() override {};
};

class runNode : public ASTNode
{
public:
    runNode(string& func, string& lib);
    void performAction() override;
};

class optionalWsNode : public ASTNode
{
public:
    optionalWsNode();
};

class wsNode : public ASTNode
{
public:
    wsNode();
};

class endlNode : public ASTNode
{
public:
    endlNode();
};
