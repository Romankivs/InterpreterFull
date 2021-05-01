#pragma once
#include "Additional.h"
#include "STNode.h"
#include <map>
class SyntaxAnalizer
{
    public:
        SyntaxAnalizer(const vector<Token>& anInput);
        ~SyntaxAnalizer();
        void setInput(const vector<Token>& inp);
        void getNext();

        bool accept(Lexema type);
        void error(const string msg);
        ASTNode* getResult();
        ASTNode* buildTree();
        void printTree();

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
        void varSubstitution(ASTNode* &node);
    private:
        vector<Token>::iterator iter;
        vector<Token> input;
        Token currentToken;
        ASTNode* resultRoot;
        bool treeSuccessfulyConstructed;
        map<Lexema, void(SyntaxAnalizer::*)(ASTNode*&)> possibleCmds = {{Lexema::ECHO, &SyntaxAnalizer::echo},
                                                                      {Lexema::QUIT, &SyntaxAnalizer::quit},
                                                                      {Lexema::ARGC, &SyntaxAnalizer::argc},
                                                                      {Lexema::ARGV, &SyntaxAnalizer::argv},
                                                                      {Lexema::ENVP, &SyntaxAnalizer::envp},
                                                                      {Lexema::HELP, &SyntaxAnalizer::help},
                                                                      {Lexema::VARS, &SyntaxAnalizer::vars},
                                                                      {Lexema::RUN, &SyntaxAnalizer::run}};
};


