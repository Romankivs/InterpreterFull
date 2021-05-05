#pragma once
#include "STNodeData.h"

class Visitor;

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void print() = 0;
    virtual void accept(Visitor &v) {};
    variant<fullCmdData, equalSignData, cmdData, echoData, runData, rawData, varSubstitutionData, stringData> NodeData;
};

struct fullCmdNode : public ASTNode
{
    fullCmdNode();
    ~fullCmdNode();
    void accept(Visitor &v) override;
    void print() override;
};

struct equalSignNode : public ASTNode
{
    equalSignNode(ASTNode* const varName, ASTNode* const varValue);
    ~equalSignNode();
    void accept(Visitor &v) override;
    void print() override;
};

struct cmdNode : public ASTNode
{
    cmdNode();
    ~cmdNode();
    void accept(Visitor &v) override;
    void print() override;
};

struct rawNode : public ASTNode
{
    rawNode(const vector<ASTNode*> inp);
    ~rawNode();
    void accept(Visitor &v) override;
    void print() override;
};

struct varSubstitutionNode : public ASTNode
{
    varSubstitutionNode();
    varSubstitutionNode(const string& varName);
    void accept(Visitor &v) override;
    void print() override;
};

struct stringNode : public ASTNode
{
    stringNode(const string& inpStr);
    void accept(Visitor &v) override;
    void print() override;
};

struct echoNode : public ASTNode
{
    echoNode();
    ~echoNode();
    void accept(Visitor &v) override;
    void print() override;
};

struct argcNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct argvNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct envpNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct quitNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct helpNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct varsNode : public ASTNode
{
    void accept(Visitor &v) override;
    void print() override;
};

struct runNode : public ASTNode
{
    runNode();
    ~runNode();
    runNode(ASTNode* const func, ASTNode* const lib);
    void accept(Visitor &v) override;
    void print() override;
};
