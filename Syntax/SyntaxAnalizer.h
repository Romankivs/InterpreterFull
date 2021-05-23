#pragma once
#include "../Syntax/Nodes/STNode.h"
#include "../LexAnalizer/LexAnalizer.h"

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
    void save(ASTNode* &node);
    void load(ASTNode* &node);
    void purge(ASTNode* &node);
    void equalSign(ASTNode* &node);
    void rawUntilFound(ASTNode* &node, initializer_list<Lexema> terminators); // works until finds a terminator lex
    void varSubstitution(ASTNode* &node);
private:
    size_t index;
    Token currentToken;
    vector<Token> inputTokens;
    LexAnalizer* inputSrc;
    ASTNode* resultRoot;
    map<Lexema, void(SyntaxAnalizer::*)(ASTNode*&)> possibleCmds = {{Lexema::ECHO, &SyntaxAnalizer::echo},
                                                              {Lexema::QUIT, &SyntaxAnalizer::quit},
                                                              {Lexema::ARGC, &SyntaxAnalizer::argc},
                                                              {Lexema::ARGV, &SyntaxAnalizer::argv},
                                                              {Lexema::ENVP, &SyntaxAnalizer::envp},
                                                              {Lexema::HELP, &SyntaxAnalizer::help},
                                                              {Lexema::VARS, &SyntaxAnalizer::vars},
                                                              {Lexema::RUN, &SyntaxAnalizer::run},
                                                              {Lexema::SAVE, &SyntaxAnalizer::save},
                                                              {Lexema::LOAD, &SyntaxAnalizer::load},
                                                              {Lexema::PURGE, &SyntaxAnalizer::purge}};
};


