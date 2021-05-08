#pragma once
#include "STNode.h"
#include "LexAnalizer.h"

class SyntaxAnalizer
{
public:
    SyntaxAnalizer(LexAnalizer* const inpLex);
    ~SyntaxAnalizer();
    void getNext();
    void unGet();

    bool accept(Lexema type);
    bool curTokEqual(Lexema type);
    void warning(const string msg);
    ASTNode* getResult();
    ASTNode* buildTree();
    Token searchForRightFunc(const string& inp);

    void cmd(ASTNode* &node);
    void echo(ASTNode* &node);
    void quit(ASTNode* &node);
    void argc(ASTNode* &node);
    void argv(ASTNode* &node);
    void envp(ASTNode* &node);
    void help(ASTNode* &node);
    void vars(ASTNode* &node);
    void run(ASTNode* &node);
    void equalSign(ASTNode* &node);
    void raw(ASTNode* &node);
    void rawWithoutSpaces(ASTNode* &node);
    void varSubstitution(ASTNode* &node);
private:
    size_t index;
    Token currentToken;
    vector<Token> inputTokens;
    LexAnalizer* inputSrc;
    ASTNode* resultRoot;
    map<string, Lexema> posCmds = {{"echo", Lexema::ECHO},
                                   {"quit", Lexema::QUIT},
                                   {"argc", Lexema::ARGC},
                                   {"argv", Lexema::ARGV},
                                   {"envp", Lexema::ENVP},
                                   {"help", Lexema::HELP},
                                   {"vars", Lexema::VARS},
                                   {"run", Lexema::RUN}};
};


