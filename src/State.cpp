#include "State.h"

int LevensteinDistance(const string& first, const string& second) // uses Wagner–Fischer algorithm
{
    const int firstLen = first.length() + 1;
    const int secondLen = second.length() + 1;
    int firstArr[secondLen + 1];
    int secondArr[secondLen + 1];

    for (int i = 0; i < secondLen + 1; ++i)
        firstArr[i] = i;
    int substitutionCost;
    for (int i = 0; i < firstLen; ++i)
    {
        secondArr[0] = i + 1;
        for (int j = 0; j < secondLen; ++j)
        {
            int deletionCost = firstArr[j + 1] + 1;
            int insertionCost = secondArr[j] + 1;
            if (first[i] == second[j])
                substitutionCost = firstArr[j];
            else
                substitutionCost = firstArr[j] + 1;
            secondArr[j + 1] = min({deletionCost, insertionCost, substitutionCost});
        }
        for (int i = 0; i < secondLen + 1; ++i)
            firstArr[i]=secondArr[i];
    }
    return firstArr[secondLen];
}

int State::minLevensteinDistanceBetweenStates()
{
    int minDistance = INT_MAX;
    for (size_t i = 0; i < stateToString.size(); ++i)
    {
        for (size_t j = i + 1; j < stateToString.size(); ++j)
        {
            int tmpDist = LevensteinDistance(stateToString[i], stateToString[j]);
            if (tmpDist < minDistance)
                minDistance = tmpDist;
        }
    }
    return minDistance;
}
