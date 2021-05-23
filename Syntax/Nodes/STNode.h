#pragma once
#include "STNodeData.h"

class Visitor;

struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void accept(Visitor &v) {};
    variant<fullCmdData, equalSignData, cmdData, echoData, runData,
        rawData, varSubstitutionData, saveData, loadData,
        stringData> NodeData;
};

struct fullCmdNode : public ASTNode
{
    fullCmdNode();
    ~fullCmdNode();
    void accept(Visitor &v) override;

};

struct equalSignNode : public ASTNode
{
    equalSignNode(ASTNode* const varName, ASTNode* const varValue);
    ~equalSignNode();
    void accept(Visitor &v) override;

};

struct cmdNode : public ASTNode
{
    cmdNode();
    ~cmdNode();
    void accept(Visitor &v) override;

};

struct rawNode : public ASTNode
{
    rawNode(const vector<ASTNode*> inp);
    ~rawNode();
    void accept(Visitor &v) override;

};

struct varSubstitutionNode : public ASTNode
{
    varSubstitutionNode();
    varSubstitutionNode(ASTNode* node);
    ~varSubstitutionNode();
    void accept(Visitor &v) override;

};

struct stringNode : public ASTNode
{
    stringNode(const string& inpStr);
    void accept(Visitor &v) override;

};

struct echoNode : public ASTNode
{
    echoNode();
    ~echoNode();
    void accept(Visitor &v) override;

};

struct argcNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct argvNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct envpNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct quitNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct helpNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct varsNode : public ASTNode
{
    void accept(Visitor &v) override;

};

struct runNode : public ASTNode
{
    runNode();
    ~runNode();
    runNode(ASTNode* const func, ASTNode* const lib);
    void accept(Visitor &v) override;

};

struct saveNode : public ASTNode
{
    saveNode();
    ~saveNode();
    void accept(Visitor &v) override;

};

struct loadNode : public ASTNode
{
    loadNode();
    ~loadNode();
    void accept(Visitor &v) override;
};

struct purgeNode : public ASTNode
{
    void accept(Visitor &v) override;
};

