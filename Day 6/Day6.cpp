#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;

void PartOne();
void PartTwo();

int main()
{
  PartTwo();

  return 0;
}

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  unordered_set<char> questions;
  int                 sum = 0;

  auto values = reader.ReadStrings();
  for (const auto & value : values)
  {
    if (value.empty())
    {
      sum += questions.size();
      questions = {};
    }
    else
    {
      for (size_t i = 0; i < value.size(); i++)
        questions.insert(value[i]);
    }
  }

  cout << sum;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  unordered_map<char, int> questionCount;
  int                      rows = 0, sum = 0;

  auto values = reader.ReadStrings();
  for (const auto & value : values)
  {
    if (value.empty())
    {
      for (const auto & [question, count] : questionCount)
      {
        if (count == rows)
          sum++;
      }

      questionCount = {};
      rows          = 0;
    }
    else
    {
      for (size_t i = 0; i < value.size(); i++)
        questionCount[value[i]]++;

      rows++;
    }
  }

  cout << sum;
}
