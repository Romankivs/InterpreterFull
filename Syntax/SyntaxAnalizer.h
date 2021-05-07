#pragma once
#include "Additional.h"
#include "STNode.h"
#include "LexAnalizer.h"

class SyntaxAnalizer
{
    public:
        SyntaxAnalizer(LexAnalizer* const inpLex);
        ~SyntaxAnalizer();
        void getNext();

        bool accept(Lexema type);
        bool curTokEqual(Lexema type);
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
    //private:
        size_t index;
        LexAnalizer* inputSrc;
        Token currentToken;
        ASTNode* resultRoot;
        bool treeSuccessfulyConstructed;
};


