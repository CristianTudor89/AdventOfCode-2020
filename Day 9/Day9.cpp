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

void PartOne()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto vals   = reader.ReadValues<long long>();
  int  offset = 25;

  for (size_t i = offset; i < vals.size(); i++)
  {
    bool found = false;
    for (size_t j = i - offset; j < i - 1; j++)
    {
      for (size_t k = j + 1; k < i; k++)
      {
        if (vals[j] + vals[k] == vals[i])
        {
          found = true;
          j     = i - 1;
          break;
        }
      }
    }

    if (!found)
      cout << vals[i];
  }
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto      vals   = reader.ReadValues<long long>();
  int       offset = 25;
  long long val    = 0;

  for (size_t i = offset; i < vals.size(); i++)
  {
    bool found = false;
    for (size_t j = i - offset; j < i - 1; j++)
    {
      for (size_t k = j + 1; k < i; k++)
      {
        if (vals[j] + vals[k] == vals[i])
        {
          found = true;
          j     = i - 1;
          break;
        }
      }
    }

    if (!found)
      val = vals[i];
  }

  size_t    i     = 0;
  int       begin = 0, end = 0;
  long long sum = 0;

  while (i < vals.size())
  {
    sum += vals[i];
    end = i++;

    if (sum == val)
    {
      if (end - begin >= 1)
      {
        auto min = std::min_element(vals.begin() + begin, vals.begin() + end);
        auto max = std::max_element(vals.begin() + begin, vals.begin() + end);

        cout << *min + *max;
        break;
      }
    }
    else if (sum > val)
    {
      i   = ++begin;
      sum = 0;
    }
  }
}
