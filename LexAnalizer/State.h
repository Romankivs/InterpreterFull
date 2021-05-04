#pragma once
#include <string>
#include <map>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

int LevensteinDistance(const string& first, const string& second);

class State
{
public:
    enum PossibleStates
    {
        INSIDE_QUOTATION_MARKS,
        OUTSIDE_QUOTATION_MARKS,
        NAME_S,
        WHITESPACE,
        WAITING
    };
    int minLevensteinDistanceBetweenStates();
private:
    vector<string> stateToString = {"INSIDE_QUOTATION_MARKS",
                                    "OUTSIDE_QUOTATION_MARKS",
                                    "NAME_S",
                                    "WHITESPACE",
                                    "WAITING"
                                   };
};

