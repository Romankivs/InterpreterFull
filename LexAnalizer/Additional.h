#pragma once
#include <string>

using namespace std;

enum Lexema
{
    DOLLAR_SIGN,
    EQUAL_SIGN,
    OPEN_BRACE,
    CLOSE_BRACE,
    STRING,
    NAME,
    WHITESPACE,
    END_OF_LINE,
    ECHO,
    QUIT,
    ARGC,
    ARGV,
    ENVP,
    HELP,
    VARS,
    RUN,
    SAVE,
    LOAD,
    PURGE
};

string lexemaToString(Lexema lex); // just for demonstrational purposes

struct Token
{
    Lexema type;
    string value;
};

struct AnalizerInput
{
    string input;
    size_t index;
};
