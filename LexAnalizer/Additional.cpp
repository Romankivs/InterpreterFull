#include "Additional.h"

string lexemaToString(Lexema lex)
{
    switch(lex)
    {
        case Lexema::DOLLAR_SIGN: return "dollar"; break;
        case Lexema::EQUAL_SIGN: return "equal"; break;
        case Lexema::OPEN_BRACE: return "openBrac"; break;
        case Lexema::CLOSE_BRACE: return "closeBrac"; break;
        case Lexema::STRING: return "string"; break;
        case Lexema::NAME: return "name"; break;
        case Lexema::WHITESPACE: return "whitespace"; break;
        case Lexema::END_OF_LINE: return "endl"; break;
        case Lexema::ECHO: return "echo"; break;
        case Lexema::QUIT: return "quit"; break;
        case Lexema::ARGC: return "argc"; break;
        case Lexema::ARGV: return "argv"; break;
        case Lexema::ENVP: return "envp"; break;
        case Lexema::HELP: return "help"; break;
        case Lexema::VARS: return "vars"; break;
        case Lexema::RUN: return "run"; break;
        case Lexema::SAVE: return "save"; break;
        case Lexema::LOAD: return "load"; break;
        case Lexema::PURGE: return "purge"; break;
        default: return "unknown";
    }
}
