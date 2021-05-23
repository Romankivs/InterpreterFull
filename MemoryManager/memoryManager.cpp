#include "memoryManager.h"

void memoryManager::assignValueToVar(const string name, const string value)
{
    storageDict[name] = value;
}

string memoryManager::getVarValue(const string name)
{
    return storageDict[name];
}

string memoryManager::listAllVars()
{
    if (storageDict.empty())
        return "Currently, there are no variables\n";
    string result = "Variables:\n";
    for(auto it : storageDict)
        result += it.first + "=" + it.second + "\n";
    return result;
}


