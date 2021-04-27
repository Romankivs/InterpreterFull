#pragma once
#include "Additional.h"
#include "STNode.h"
#include <map>
class SyntaxAnalizer
{
    public:
        SyntaxAnalizer(vector<Token>& anInput);
        void setInput(vector<Token>& inp);
        void getNext();

        bool accept(Lexema type);
        bool expect(Lexema type);

        shared_ptr<ASTNode> getResult();
        shared_ptr<ASTNode> buildTree();
        void cmd(shared_ptr<ASTNode> node);
        void echo(shared_ptr<ASTNode> node);
        void quit(shared_ptr<ASTNode> node);
        void argc(shared_ptr<ASTNode> node);
        void argv(shared_ptr<ASTNode> node);
        void envp(shared_ptr<ASTNode> node);
        void help(shared_ptr<ASTNode> node);
        void vars(shared_ptr<ASTNode> node);
        void run(shared_ptr<ASTNode> node);
        void equalSign(shared_ptr<ASTNode> node);
        void raw(shared_ptr<ASTNode> node);
    private:
        vector<Token>::iterator iter;
        shared_ptr<vector<Token>> input;
        Token currentToken;
        shared_ptr<ASTNode> resultRoot;
        map<Lexema, void(SyntaxAnalizer::*)(shared_ptr<ASTNode>)> possibleCmds = {{Lexema::ECHO, &SyntaxAnalizer::echo},
                                                                      {Lexema::QUIT, &SyntaxAnalizer::quit},
                                                                      {Lexema::ARGC, &SyntaxAnalizer::argc},
                                                                      {Lexema::ARGV, &SyntaxAnalizer::argv},
                                                                      {Lexema::ENVP, &SyntaxAnalizer::envp},
                                                                      {Lexema::HELP, &SyntaxAnalizer::help},
                                                                      {Lexema::VARS, &SyntaxAnalizer::vars},
                                                                      {Lexema::RUN, &SyntaxAnalizer::run}};
};


