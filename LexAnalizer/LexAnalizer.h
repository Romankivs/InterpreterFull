#pragma once
#include <iostream>
#include "State.h"
#include "Additional.h"

class LexAnalizer
{
public:
    LexAnalizer();
    void setInputString(const string& inputStr);
    Token getToken();
private:
    void FinishTokenCreation(Lexema lex);
    void continueSequence();

    void openCurlyBrac();
    void closeCurlyBrac();

    void beginUnquotatedString();
    void endUnquotatedString();

    void beginQuotationMarks();
    void endQuotationMarks();

    void beginName();
    void endName();

    void dollarSign();
    void equalSign();

    void beginWhitespace();
    void endWhitespace();

    void endLine();

    State::PossibleStates currentState;
    Token result;
    bool isTokenFinished;
    AnalizerInput analizerInput;
    map<pair<char, State::PossibleStates>, void(LexAnalizer::*)()> functions;
    map<string, Lexema> possibleCmds = {{"echo", Lexema::ECHO},
                                        {"quit", Lexema::QUIT},
                                        {"argc", Lexema::ARGC},
                                        {"argv", Lexema::ARGV},
                                        {"envp", Lexema::ENVP},
                                        {"help", Lexema::HELP},
                                        {"vars", Lexema::VARS},
                                        {"run", Lexema::RUN}};
};




