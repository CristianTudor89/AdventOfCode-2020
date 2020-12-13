#include "Algorithm.h"
#include "Input.h"
#include "StringUtil.h"

using namespace StringUtil;
using namespace Algorithm;

struct Bus
{
  int id;
  int index;
};

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

  auto values = reader.ReadStrings();
  int  bus    = stoi(values[0]);

  vector<int> busIds;

  auto tokens = TokenizeString(values[1], ",");
  for (const auto & token : tokens)
  {
    if (token != "x")
      busIds.push_back(stoi(token));
  }

  int min = 1000000, pos = 0;
  for (int i = 0; i < busIds.size(); i++)
  {
    int amount = busIds[i] - (bus % busIds[i]);
    if (amount < min)
    {
      min = amount;
      pos = i;
    }
  }

  cout << busIds[pos] * min;
}

void PartTwo()
{
  ifstream    input("in.txt");
  InputReader reader(input);

  auto values = reader.ReadStrings();
  auto tokens = TokenizeString(values[1], ",");

  vector<Bus> busVec;

  for (int i = 0; i < tokens.size(); i++)
  {
    if (tokens[i] != "x")
      busVec.push_back({ stoi(tokens[i]), i });
  }

  unsigned long long numberToTest = 0;
  int                offset       = 2;

  while (true)
  {
    numberToTest += busVec[offset].id;

    bool found = true;
    for (int i = 0; i < busVec.size(); i++)
    {
      if (i != offset &&
          (numberToTest + busVec[i].index - busVec[offset].index) % busVec[i].id != 0)
      {
        found = false;
        break;
      }
    }

    if (found)
    {
      cout << numberToTest - busVec[offset].index;
      break;
    }
  }
}
