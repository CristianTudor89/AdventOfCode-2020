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

  int  count   = 0;
  auto strings = reader.ReadStrings();

  for (const auto & str : strings)
  {
    auto tokens = TokenizeString(str);

    auto [lowerBound, upperBound] = GetBounds(tokens[0]);
    char   letter                 = tokens[1][0];
    string str                    = tokens[2];

    int nr = std::count(str.begin(), str.end(), letter);
    if (lowerBound <= nr && nr <= upperBound)
      count++;
  }

  cout << count;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  int  count   = 0;
  auto strings = reader.ReadStrings();

  for (const auto & str : strings)
  {
    auto tokens = TokenizeString(str);

    auto [lowerBound, upperBound] = GetBounds(tokens[0]);
    char   letter                 = tokens[1][0];
    string str                    = tokens[2];

    if ((str[lowerBound - 1] == letter && str[upperBound - 1] != letter) ||
        (str[lowerBound - 1] != letter && str[upperBound - 1] == letter))
      count++;
  }

  cout << count;
}
