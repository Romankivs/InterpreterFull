#pragma once
#include <vector>
#include <iostream>
#include <variant>
#include <memory>

using namespace std;

class ASTNode;
class cmdNode;
class rawNode;

struct fullCmdData{
    ASTNode* command;
};

struct equalSignData{
     string varName, varValue;
};

struct cmdData{
    ASTNode* cmd;
};

struct echoData{
    ASTNode* raw;
};

struct runData{
    string func, lib;
};

struct rawData{
     vector<string> rawStr;
};

class ASTNode
{
public:
    virtual void performAction() {}; //reserved for later usage
    virtual ~ASTNode() = default;
    variant<fullCmdData, equalSignData, cmdData, echoData, runData, rawData> NodeData;
    int a;
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
    equalSignNode();
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
    ~cmdNode() { delete get<cmdData>(NodeData).cmd;}
    void performAction() override;
};

class fullCmdNode : public ASTNode
{
public:
    fullCmdNode();
    ~fullCmdNode() { delete get<fullCmdData>(NodeData).command;}
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
    ~echoNode() { delete get<echoData>(NodeData).raw;}
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
    runNode();
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
