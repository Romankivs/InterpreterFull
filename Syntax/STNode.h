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

struct varSubstitutionData { string variable; };

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void evaluate() {}; //reserved for later usage

    variant<fullCmdData, equalSignData, cmdData, echoData, runData, rawData> NodeData;
};

struct equalSignNode : public ASTNode
{
    void evaluate() override;
};

struct cmdNode : public ASTNode
{
    ~cmdNode() { delete get<cmdData>(NodeData).cmd;}
    void evaluate() override;
};

struct fullCmdNode : public ASTNode
{
    ~fullCmdNode() { delete get<fullCmdData>(NodeData).command;}
    void evaluate() override;
};

struct rawNode : public ASTNode
{
    void evaluate() override;
};

struct varSubstitutionNode : public ASTNode
{
    void evaluate() override {};
};

struct echoNode : public ASTNode
{
    ~echoNode() { delete get<echoData>(NodeData).raw;}
    void evaluate() override;
};

struct argcNode : public ASTNode
{
    void evaluate() override;
};

struct argvNode : public ASTNode
{
    void evaluate() override;
};

struct envpNode : public ASTNode
{
    void evaluate() override;
};

struct quitNode : public ASTNode
{
    void evaluate() override;
};

struct helpNode : public ASTNode
{
    helpNode() {};
    void evaluate() override;
};

struct varsNode : public ASTNode
{
    void evaluate() override;
};

struct runNode : public ASTNode
{
    void evaluate() override;
};
