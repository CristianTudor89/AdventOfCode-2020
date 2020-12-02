#pragma once

#include <string>
#include <vector>
using namespace std;

namespace StringUtil
{
vector<char>   GetCharVector(const string & aStr);
vector<string> TokenizeString(const string & aStr, const string & aSeparator = " ");
pair<int, int> GetBounds(const string & aStr, const string & aSeparator = "-");
};  // namespace StringUtil
