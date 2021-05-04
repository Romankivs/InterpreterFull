#include "memoryManager.h"

void memoryManager::assignValueToVar(const string name, const string value)
{
    storageDict[name] = value;
}

string memoryManager::getVarValue(const string name)
{
    return storageDict[name];
}
