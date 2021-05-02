#pragma once
#include "STNodeData.h"

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void print() = 0;
    variant<fullCmdData, equalSignData, cmdData, echoData, runData, rawData, varSubstitutionData> NodeData;
};

struct equalSignNode : public ASTNode
{
    equalSignNode(const string& varName, const string& varValue);
    void print() override;
};

struct cmdNode : public ASTNode
{
    cmdNode();
    ~cmdNode() { delete get<cmdData>(NodeData).cmd;}
    void print() override;
};

struct fullCmdNode : public ASTNode
{
    fullCmdNode();
    ~fullCmdNode() { delete get<fullCmdData>(NodeData).command;}
    void print() override;
};

struct rawNode : public ASTNode
{
    rawNode(const vector<string>& inp);
    void print() override;
};

struct varSubstitutionNode : public ASTNode
{
    varSubstitutionNode(const string& varName);
    void print() override;
};

struct echoNode : public ASTNode
{
    echoNode();
    ~echoNode() { delete get<echoData>(NodeData).raw;}
    void print() override;
};

struct argcNode : public ASTNode
{
    void print() override;
};

struct argvNode : public ASTNode
{
    void print() override;
};

struct envpNode : public ASTNode
{
    void print() override;
};

struct quitNode : public ASTNode
{
    void print() override;
};

struct helpNode : public ASTNode
{
    void print() override;
};

struct varsNode : public ASTNode
{
    void print() override;
};

struct runNode : public ASTNode
{
    runNode(const string& lib, const string& func);
    void print() override;
};
