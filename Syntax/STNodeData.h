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
