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

struct equalSignData{ ASTNode* varName, *varValue; };

struct cmdData{ ASTNode* cmd;};

struct echoData{ ASTNode* raw; };

struct runData{ ASTNode* func, *lib; };

struct rawData{ vector<ASTNode*> rawStr; };

struct varSubstitutionData { ASTNode* variable; };

struct saveData{ ASTNode* fileName; };

struct loadData{ ASTNode* fileName; };

struct stringData{ string value; };
