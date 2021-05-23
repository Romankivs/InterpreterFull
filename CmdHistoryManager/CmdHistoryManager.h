#pragma once
#include <fstream>
#include <istream>
#include <iterator>
#include <string>

using namespace std;

class CmdHistoryManager
{
public:
    void addToBuffer(const string& inp);
    void loadHistoryFromFile(const string& fileName);
    void saveHistoryToFile(const string& fileName);
    void clearBuffer();
//private:
    string cmdHistoryBuffer;
};

