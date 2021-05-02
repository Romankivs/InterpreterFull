#include "LexAnalizer.h"

LexAnalizer::LexAnalizer() // Constructor initialized automatas table
{
    // Initial table //
    for (int c = 0; c < 256; ++c)
    {
        functions[make_pair(c, State::INSIDE_QUOTATION_MARKS)] = &LexAnalizer::continueSequence;
        functions[make_pair(c, State::OUTSIDE_QUOTATION_MARKS)] = &LexAnalizer::continueSequence;
        functions[make_pair(c, State::WHITESPACE)] = &LexAnalizer::endWhitespace;
        if (isalpha(c))
            functions[make_pair(c, State::WAITING)] = &LexAnalizer::beginName;
        else
            functions[make_pair(c, State::WAITING)] = &LexAnalizer::beginUnquotatedString;
        if (isalnum(c))
            functions[make_pair(c, State::NAME_S)] = &LexAnalizer::continueSequence;
        else
            functions[make_pair(c, State::NAME_S)] = &LexAnalizer::beginUnquotatedString;
    }
    // Special characters that end Name and UnquotatedString lexems //
    vector<char> specialCharacters = { '\0', ' ', '$', '{', '}', '=', '\n' };
    for (auto c : specialCharacters)
    {
        functions[make_pair(c, State::OUTSIDE_QUOTATION_MARKS)] = &LexAnalizer::endUnquotatedString;
        functions[make_pair(c, State::NAME_S)] = &LexAnalizer::endName;
    }
    // Quotation Marks //
    functions[make_pair('\"', State::INSIDE_QUOTATION_MARKS)] = &LexAnalizer::endQuotationMarks;
    functions[make_pair('\"', State::OUTSIDE_QUOTATION_MARKS)] = &LexAnalizer::beginQuotationMarks;
    functions[make_pair('\"', State::NAME_S)] = &LexAnalizer::beginQuotationMarks;
    functions[make_pair('\"', State::WAITING)] = &LexAnalizer::beginQuotationMarks;
    // endl characters //
    vector<char> endlChars = {'\0', '\n'};
    for (auto c : endlChars)
    {
        functions[make_pair(c, State::INSIDE_QUOTATION_MARKS)] = &LexAnalizer::endQuotationMarks;
        functions[make_pair(c, State::WAITING)] = &LexAnalizer::endLine;
        functions[make_pair(c, State::WHITESPACE)] = &LexAnalizer::endLine;
    }
    // Special characters unique functions//
    functions[make_pair(' ', State::WAITING)] = &LexAnalizer::beginWhitespace;
    functions[make_pair(' ', State::WHITESPACE)] = &LexAnalizer::continueSequence;
    functions[make_pair('$', State::WAITING)] = &LexAnalizer::dollarSign;
    functions[make_pair('{', State::WAITING)] = &LexAnalizer::openCurlyBrac;
    functions[make_pair('}', State::WAITING)] = &LexAnalizer::closeCurlyBrac;
    functions[make_pair('=', State::WAITING)] = &LexAnalizer::equalSign;
    //~~~~~~~~~~~~~~~~~~~~//
}

void LexAnalizer::FinishTokenCreation(Lexema lex)
{
    result.type = lex;
    isTokenFinished = true;
}

void LexAnalizer::setInputString(const string& inputStr)
{
    isTokenFinished = false;
    analizerInput.input = inputStr;
    analizerInput.index = 0;
    currentState = State::WAITING;
}

Token LexAnalizer::getToken()
{
    result.value.clear();
    isTokenFinished = false;
    while (!isTokenFinished && analizerInput.index <= analizerInput.input.length())
    {
        (*this.*functions[make_pair(analizerInput.input[analizerInput.index], currentState)])();
        analizerInput.index += 1;
    }
    return result;
}

void LexAnalizer::continueSequence()
{
    result.value += analizerInput.input[analizerInput.index];
}

void LexAnalizer::dollarSign()
{
    result.value += "$";
    FinishTokenCreation(Lexema::DOLLAR_SIGN);
}

void LexAnalizer::openCurlyBrac()
{
    result.value += "{";
    FinishTokenCreation(Lexema::OPEN_BRACE);
}

void LexAnalizer::closeCurlyBrac()
{
    result.value += "}";
    FinishTokenCreation(Lexema::CLOSE_BRACE);
}

void LexAnalizer::equalSign()
{
    result.value += "=";
    FinishTokenCreation(Lexema::EQUAL_SIGN);
}

void LexAnalizer::beginQuotationMarks()
{
    currentState = State::INSIDE_QUOTATION_MARKS;
}

void LexAnalizer::endQuotationMarks()
{
    currentState = State::WAITING;
    FinishTokenCreation(Lexema::STRING);
    if (analizerInput.input[analizerInput.index] != '\"') // if terminated
        analizerInput.index -= 1;
}

void LexAnalizer::beginName()
{
    currentState = State::NAME_S;
    result.value += analizerInput.input[analizerInput.index];
}

void LexAnalizer::endName()
{
    currentState = State::WAITING;
    if (possibleCmds.contains(result.value))
        FinishTokenCreation(possibleCmds[result.value]);
    else
        FinishTokenCreation(Lexema::NAME);
    analizerInput.index -= 1;
}

void LexAnalizer::beginUnquotatedString()
{
    currentState = State::OUTSIDE_QUOTATION_MARKS;
    result.value += analizerInput.input[analizerInput.index];
}

void LexAnalizer::endUnquotatedString()
{
    currentState = State::WAITING;
    FinishTokenCreation(Lexema::STRING);
    analizerInput.index -= 1;
}

void LexAnalizer::beginWhitespace()
{
    currentState = State::WHITESPACE;
    result.value += analizerInput.input[analizerInput.index];
}

void LexAnalizer::endWhitespace()
{
    currentState = State::WAITING;
    FinishTokenCreation(Lexema::WHITESPACE);
    analizerInput.index -= 1;
}

void LexAnalizer::endLine()
{
    result.value += analizerInput.input[analizerInput.index];
    FinishTokenCreation(Lexema::END_OF_LINE);
}
