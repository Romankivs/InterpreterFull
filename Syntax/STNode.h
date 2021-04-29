#pragma once
#include <vector>
#include <iostream>
#include <variant>
#include <memory>

using namespace std;

struct ASTNode;
struct cmdNode;
struct rawNode;

struct fullCmdData{ ASTNode* command; };

struct equalSignData{ string varName, varValue; };

struct cmdData{ ASTNode* cmd;};

struct echoData{ ASTNode* raw; };

struct runData{ string func, lib; };

struct rawData{ vector<string> rawStr; };

struct ASTNode
{
    virtual void performAction() {}; //reserved for later usage
    virtual ~ASTNode() = default;
    variant<fullCmdData, equalSignData, cmdData, echoData, runData, rawData> NodeData;
    int a;
};

struct equalSignNode : public ASTNode
{
    equalSignNode() {};
    void performAction() override {};
};

struct cmdNode : public ASTNode
{
    cmdNode() {};
    ~cmdNode() { delete get<cmdData>(NodeData).cmd;}
    void performAction() override {};
};

struct fullCmdNode : public ASTNode
{
    fullCmdNode() {};
    ~fullCmdNode() { delete get<fullCmdData>(NodeData).command;}
    void performAction() override {};
};

struct rawNode : public ASTNode
{
    rawNode() {};
    void performAction() override {}
};

struct echoNode : public ASTNode
{
    echoNode() {};
    ~echoNode() { delete get<echoData>(NodeData).raw;}
    void performAction() override {};
};

struct argcNode : public ASTNode
{
    argcNode() {};
    void performAction() override {};
};

struct argvNode : public ASTNode
{
    argvNode() {};
    void performAction() override {};
};

struct envpNode : public ASTNode
{
    envpNode() {};
    void performAction() override {};
};

struct quitNode : public ASTNode
{
    quitNode() {};
    void performAction() override {};
};

struct helpNode : public ASTNode
{
    helpNode() {};
    void performAction() override {};
};

struct varsNode : public ASTNode
{
    varsNode() {};
    void performAction() override {};
};

struct runNode : public ASTNode
{
    runNode() {};
    void performAction() override {};
};
