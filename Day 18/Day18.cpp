#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

void ComputeResult(string & aStr)
{
  bool hasOperators = true;
  while (hasOperators)
  {
    int endPos = -1;
    for (int i = 0; i < aStr.size(); i++)
    {
      long long result = 0;

      if (aStr[i] == '+' || aStr[i] == '*')
      {
        endPos = aStr.find(' ', i + 2);
        if (endPos == string::npos)
        {
          endPos = aStr.find(')', i + 2);
          if (endPos == string::npos)
            endPos = aStr.size();
        }

        if (aStr[i] == '+')
          result = stoll(aStr.substr(0, i - 1)) + stoll(aStr.substr(i + 2, endPos - i - 2));
        else
          result = stoll(aStr.substr(0, i - 1)) * stoll(aStr.substr(i + 2, endPos - i - 2));
      }

      if (endPos != -1)
      {
        aStr = std::to_string(result) + aStr.substr(endPos);
        break;
      }
    }

    if (endPos == -1)
      hasOperators = false;
  }
}

void ComputeResultDiffPrecedence(string & aStr)
{
  bool hasAdditionOperators = true;
  while (hasAdditionOperators)
  {
    int beginPos = 0, endPos = -1;
    for (int i = 0; i < aStr.size(); i++)
    {
      long long result = 0;

      if (aStr[i] == '*')
      {
        beginPos = i + 2;
      }
      else if (aStr[i] == '+')
      {
        endPos = aStr.find(' ', i + 2);
        if (endPos == string::npos)
        {
          endPos = aStr.find(')', i + 2);
          if (endPos == string::npos)
            endPos = aStr.size();
        }

        result = stoll(aStr.substr(beginPos, i - 1)) + stoll(aStr.substr(i + 2, endPos - i - 2));
      }

      if (endPos != -1)
      {
        aStr = aStr.substr(0, beginPos) + std::to_string(result) + aStr.substr(endPos);
        break;
      }
    }

    if (endPos == -1)
      hasAdditionOperators = false;
  }

  bool hasMultiplyOperators = true;
  while (hasMultiplyOperators)
  {
    int endPos = -1;
    for (int i = 0; i < aStr.size(); i++)
    {
      long long result = 0;

      if (aStr[i] == '*')
      {
        endPos = aStr.find(' ', i + 2);
        if (endPos == string::npos)
        {
          endPos = aStr.find(')', i + 2);
          if (endPos == string::npos)
            endPos = aStr.size();
        }

        result = stoll(aStr.substr(0, i - 1)) * stoll(aStr.substr(i + 2, endPos - i - 2));
      }

      if (endPos != -1)
      {
        aStr = std::to_string(result) + aStr.substr(endPos);
        break;
      }
    }

    if (endPos == -1)
      hasMultiplyOperators = false;
  }
}

void Solution(bool aPartTwo)
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto strings = reader.ReadStrings();

  long long sum = 0;
  for (auto & str : strings)
  {
    bool hasParentheses = true;

    while (hasParentheses)
    {
      int beginPos = -1, endPos = -1;
      for (int i = 0; i < str.size(); i++)
      {
        if (str[i] == '(')
        {
          beginPos = i;
        }
      }

      for (int i = beginPos; i < str.size(); i++)
      {
        if (str[i] == ')')
        {
          endPos = i;
          break;
        }
      }

      if (beginPos == -1)
        hasParentheses = false;
      else
      {
        string strInParentheses = str.substr(beginPos + 1, endPos - beginPos - 1);

        if (aPartTwo)
          ComputeResultDiffPrecedence(strInParentheses);
        else
          ComputeResult(strInParentheses);

        str = str.substr(0, beginPos) + strInParentheses + str.substr(endPos + 1);
      }
    }

    if (aPartTwo)
      ComputeResultDiffPrecedence(str);
    else
      ComputeResult(str);

    sum += stoll(str);
  }

  cout << sum;
}

void PartOne()
{
  Solution(false);
}

void PartTwo()
{
  Solution(true);
}
