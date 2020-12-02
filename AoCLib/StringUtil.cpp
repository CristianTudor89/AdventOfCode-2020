#include "StringUtil.h"
#include <assert.h>

vector<char> StringUtil::GetCharVector(const string & aStr)
{
  vector<char> chars(aStr.size());

  for (size_t i = 0; i < aStr.size(); i++)
    chars[i] = aStr[i];

  return chars;
}

vector<string> StringUtil::TokenizeString(const string & aStr, const string & aSeparator /*= " "*/)
{
  vector<string> values;
  size_t         initialPos = 0, pos = 0;

  while (pos != string::npos)
  {
    string str;

    pos = aStr.find(aSeparator, initialPos);
    if (pos == string::npos)
    {
      str = aStr.substr(initialPos);
    }
    else
    {
      str        = aStr.substr(initialPos, pos - initialPos);
      initialPos = pos + aSeparator.size();
    }

    values.push_back(str);
  }

  return values;
}

pair<int, int> StringUtil::GetBounds(const string & aStr, const string & aSeparator /*= "-"*/)
{
  vector<string> tokens = TokenizeString(aStr, aSeparator);

  assert(tokens.size() == 2);

  return { stoi(tokens[0]), stoi(tokens[1]) };
}
