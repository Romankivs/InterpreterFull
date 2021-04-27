#include "Additional.h"

string lexemaToString(Lexema lex)
{
    switch(lex)
    {
        case Lexema::DOLLAR_SIGN: return "Dollar"; break;
        case Lexema::EQUAL_SIGN: return "Equal"; break;
        case Lexema::OPEN_BRACE: return "OpenBrac"; break;
        case Lexema::CLOSE_BRACE: return "CloseBrac"; break;
        case Lexema::STRING: return "String"; break;
        case Lexema::NAME: return "Name"; break;
        case Lexema::WHITESPACE: return "Whitespace"; break;
        case Lexema::END_OF_LINE: return "Endl"; break;
        case Lexema::ECHO: return "Echo"; break;
        case Lexema::QUIT: return "Quit"; break;
        case Lexema::ARGC: return "Argc"; break;
        case Lexema::ARGV: return "Argv"; break;
        case Lexema::ENVP: return "Envp"; break;
        case Lexema::HELP: return "Help"; break;
        case Lexema::VARS: return "Vars"; break;
        case Lexema::RUN: return "Run"; break;
        default: return "Unknown";
    }
}
