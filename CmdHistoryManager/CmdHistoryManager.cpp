#include "CmdHistoryManager.h"

void CmdHistoryManager::addToBuffer(const string& inp)
{
    cmdHistoryBuffer += inp;
}

void CmdHistoryManager::loadHistoryFromFile(const string& fileName)
{
    ifstream inp;
    inp.open(fileName);
    std::istreambuf_iterator<char> begin(inp), end;
    cmdHistoryBuffer += string(begin, end);
    inp.close();
}

void CmdHistoryManager::saveHistoryToFile(const string& fileName)
{
    ofstream out;
    out.open(fileName);
    out << cmdHistoryBuffer;
    out.close();
}

void CmdHistoryManager::clearBuffer()
{
    cmdHistoryBuffer.clear();
}
