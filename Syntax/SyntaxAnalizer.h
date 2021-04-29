#pragma once
#include "Additional.h"
#include "STNode.h"
#include <map>
class SyntaxAnalizer
{
    public:
        SyntaxAnalizer(vector<Token>& anInput);
        ~SyntaxAnalizer();
        void setInput(vector<Token>& inp);
        void getNext();

        bool accept(Lexema type);
        bool expect(Lexema type);

        ASTNode* getResult();
        ASTNode* buildTree();

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
    private:
        vector<Token>::iterator iter;
        vector<Token> input;
        Token currentToken;
        ASTNode* resultRoot;
        map<Lexema, void(SyntaxAnalizer::*)(ASTNode*&)> possibleCmds = {{Lexema::ECHO, &SyntaxAnalizer::echo},
                                                                      {Lexema::QUIT, &SyntaxAnalizer::quit},
                                                                      {Lexema::ARGC, &SyntaxAnalizer::argc},
                                                                      {Lexema::ARGV, &SyntaxAnalizer::argv},
                                                                      {Lexema::ENVP, &SyntaxAnalizer::envp},
                                                                      {Lexema::HELP, &SyntaxAnalizer::help},
                                                                      {Lexema::VARS, &SyntaxAnalizer::vars},
                                                                      {Lexema::RUN, &SyntaxAnalizer::run}};
};


