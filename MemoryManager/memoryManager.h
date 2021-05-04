#pragma once
#include <map>
#include <string>

using namespace std;

class memoryManager
{
public:
    void assignValueToVar(const string name, const string value);
    string getVarValue(const string name);
private:
    map<string, string> storageDict;
};
